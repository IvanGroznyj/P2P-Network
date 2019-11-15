#include "MainInterfaces.h"
#include "StandartCommandInterpreter.h"
#include "ThreadRequestsHandler.h"
#include <cstring>
#include <thread>
#include <unistd.h>
#include <fstream>
using namespace std;

ICommandInterpreter *global_cmd_interpeter;
Translator cmd_translator;
thread *mainThread = nullptr;

void ThreadAnswer(ISocketWorker *sworker, int sock_id){
	char *buffer;
	int bytes_read = 1024;
	string sum_buffer = "";
	while(bytes_read==1024){
		buffer = new char[1024];
		bytes_read = sworker->Recieve(sock_id, buffer, 1024);
		sum_buffer += buffer;
		delete[] buffer;
	}
	char *request_buffer = new char[sum_buffer.size()+1];
	strcpy(request_buffer, sum_buffer.c_str());
	char *result_buffer = global_cmd_interpeter->DoCommand(cmd_translator.TextToCommand(request_buffer));
	sworker->Send(sock_id, result_buffer, strlen(result_buffer)+1);
	sworker->Close(sock_id);
}

void ThreadHandler(ClientAddr* addr, ISocketWorker *socket_worker){
	int sock_id, listener_id;

	listener_id = socket_worker->GetNewSocketId();
	if(socket_worker->Bind(listener_id, addr)) exit(2);

	ofstream file_out;
	try{
		file_out.open("server_work");
		file_out<<"start";
	}catch(...){
		cout<<"Can't write to server_work";
	}
	if(file_out.is_open()) file_out.close();


	socket_worker->Listen(listener_id, 0);
	ifstream file_in;
	string buffer_str = "";
	while(1){
		file_in.open("server_work");
		buffer_str = "";
		if (file_in.is_open()){
			std::getline(file_in, buffer_str);
			file_in.close();
		}
		if(buffer_str=="stop") break;
		sock_id = socket_worker->Accept(listener_id);
		if(sock_id < 0){
			exit(3);
		}
		(new std::thread(ThreadAnswer, socket_worker, sock_id))->detach();
	}
	socket_worker->Close(listener_id);
}

void ThreadRequestsHandler::SetWorkers(ISocketWorker *socket_worker, ICommandInterpreter *cmd_interpeter){
	ThreadRequestsHandler::socket_worker = socket_worker;
	global_cmd_interpeter = cmd_interpeter;
}

void ThreadRequestsHandler::StartWorking(ClientAddr* addr){
	ThreadRequestsHandler::is_working = true;
	mainThread = new std::thread(ThreadHandler, addr, ThreadRequestsHandler::socket_worker);
	mainThread->detach();
}

int ThreadRequestsHandler::GetStatus(){
	return ThreadRequestsHandler::is_working;
}

void ThreadRequestsHandler::StopWorking(){
	ThreadRequestsHandler::is_working= false;
	ofstream file_out;
	try{
		file_out.open("server_work");
		file_out<<"stop";
	}catch(...){
		printf("Can't write to server_work");
	}
	if(file_out.is_open()) file_out.close();
}
