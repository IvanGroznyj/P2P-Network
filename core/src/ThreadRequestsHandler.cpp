/*
 *  Author: Ivan Khodyrev
 */
#include "MainInterfaces.h"
#include "StandartCommandInterpreter.h"
#include "ThreadRequestsHandler.h"
#include <cstring>
#include <thread>
#include <unistd.h>
#include <fstream>
#include <sstream>

using namespace std;
using namespace P2P_Network;

I_Command_Interpreter *global_cmd_interpeter;
Translator cmd_translator;
thread *mainThread = nullptr;

void Thread_Answer(I_Socket_Worker *sworker, int sock_id){
	char *buffer;
	int bytes_read = 1024;
	stringstream sum_buffer;
	sum_buffer << "";
	while(bytes_read==1024){
		buffer = new char[1024];
		bytes_read = sworker->recieve_buffer(sock_id, buffer, 1024);
		sum_buffer << buffer;
		delete[] buffer;
	}
	// cout<<":>"<<sum_buffer<<endl;
	char *result_buffer = global_cmd_interpeter->do_Command(cmd_translator.text_To_Command(sum_buffer.str().c_str()));
	sworker->send_buffer(sock_id, result_buffer, strlen(result_buffer)+1);
	sworker->close_socket(sock_id);
}

void Thread_Handler(Client_Addr* addr, I_Socket_Worker *socket_worker){
	int sock_id, listener_id;

	listener_id = socket_worker->get_New_Socket_Id();
	if(socket_worker->bind_socket(listener_id, addr)) exit(2);

	ofstream file_out;
	try{
		file_out.open("server_work");
		file_out<<"start";
	}catch(...){
		cout<<"Can't write to server_work";
	}
	if(file_out.is_open()) file_out.close();


	socket_worker->listen_sockets(listener_id, 0);
	ifstream file_in;
	string buffer_str = "";
	while(1){
		file_in.open("server_work");
		buffer_str = "";
		if (file_in.is_open()){
			getline(file_in, buffer_str);
			file_in.close();
		}
		if(buffer_str=="stop") break;
		sock_id = socket_worker->accept_socket(listener_id);
		if(sock_id < 0){
			break;
		}
		(new thread(Thread_Answer, socket_worker, sock_id))->detach();
	}
	socket_worker->close_socket(listener_id);
}

void Thread_Requests_Handler::set_Workers(I_Socket_Worker *socket_worker, I_Command_Interpreter *cmd_interpeter){
	Thread_Requests_Handler::socket_worker = socket_worker;
	global_cmd_interpeter = cmd_interpeter;
}

void Thread_Requests_Handler::start_Working(Client_Addr* addr){
	Thread_Requests_Handler::is_working = true;
	mainThread = new thread(Thread_Handler, addr, Thread_Requests_Handler::socket_worker);
	mainThread->detach();
}

int Thread_Requests_Handler::get_Status(){
	return Thread_Requests_Handler::is_working;
}

void Thread_Requests_Handler::stop_Working(){
	Thread_Requests_Handler::is_working= false;
	ofstream file_out;
	try{
		file_out.open("server_work");
		file_out<<"stop";
	}catch(...){
		printf("Can't write to server_work");
	}
	if(file_out.is_open()) file_out.close();
}
