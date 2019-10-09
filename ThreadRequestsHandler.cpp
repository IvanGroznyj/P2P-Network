#include "MainInterfaces.h"
#include "StandartCommandInterpreter.h"
#include "ThreadRequestsHandler.h"

ICommandInterpreter *cmdintr;
Translator tr;

void ThreadAnswer(ISocketWorker *sworker, int sock){
	char *buf;
	//char *tmpbuf;
	int bytes_read;
	string tmp = "";
	while(true){
		buf = new char[1024];
		bytes_read = sworker->Recieve(sock, buf, 1024);
		//tmpbuf = new char[bytes_read+1];
		//strncpy(tmpbuf, buf, bytes_read+1);
		tmp += buf;
		//delete[] tmpbuf;
		delete[] buf;
		if(bytes_read<1024) break;
	}
	//printf(">>> %s\n",tmp.c_str());
	char *ans = new char[tmp.size()+1];
	strcpy(ans, tmp.c_str());
	cmdintr->DoCommand(sock, tr.TextToCommand(ans));
}

void ThreadHandler(bool *isWorking, char* ip, int port, ISocketWorker *sworker){
	int sock, listener;
	listener = sworker->GetNewSocketId();
	if(sworker->Bind(listener, ip, port)){
		exit(2);
	}

	sworker->Listen(listener, 0);
	while(*isWorking){
		sock = sworker->Accept(listener);
		if(sock < 0){
			exit(3);
		}
		(new std::thread(ThreadAnswer, sworker, sock))->detach();
	}
}


	void ThreadRequestsHandler::SetWorkers(ISocketWorker *sworker, ICommandInterpreter *cmdinterpreter){
		ThreadRequestsHandler::sw = sworker;
		cmdintr = cmdinterpreter;
	}

	void ThreadRequestsHandler::StartWorking(char *ip, int port){
		ThreadRequestsHandler::isWorking = true;
		ThreadRequestsHandler::mainThreadHandler = new std::thread(ThreadHandler, &isWorking, ip, port, sw);
		ThreadRequestsHandler::mainThreadHandler->detach();
	}

	int ThreadRequestsHandler::GetStatus(){
		return ThreadRequestsHandler::isWorking;
	}

	void ThreadRequestsHandler::StopWorking(){
		ThreadRequestsHandler::isWorking = false;
	}
