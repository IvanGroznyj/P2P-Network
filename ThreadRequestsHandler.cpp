#include "MainInterfaces.h"
#include "StandartCommandInterpreter.h"
#include "ThreadRequestsHandler.h"
#include <cstring>

ICommandInterpreter *cmdintr;
Translator tr;

void ThreadAnswer(ISocketWorker *sworker, int sock){
	char *buf;
	int bytes_read;
	string tmp = "";
	while(true){
		buf = new char[1024];
		bytes_read = sworker->Recieve(sock, buf, 1024);
		tmp += buf;
		delete[] buf;
		if(bytes_read<1024) break;
	}
	char *ans = new char[tmp.size()+1];
	strcpy(ans, tmp.c_str());
	char *res = cmdintr->DoCommand(tr.TextToCommand(ans));
	sworker->Send(sock, res, strlen(res)+1);
	sworker->Close(sock);
}

void ThreadHandler(ClientAddr* addr, ISocketWorker *sworker){
	int sock, listener;
	listener = sworker->GetNewSocketId();
	if(sworker->Bind(listener, addr)){
		exit(2);
	}

	sworker->Listen(listener, 0);
	while(1){
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

	void ThreadRequestsHandler::StartWorking(ClientAddr* addr){
		ThreadRequestsHandler::isWorking = true;
		ThreadRequestsHandler::mainThreadHandler = new std::thread(ThreadHandler, addr, sw);
		ThreadRequestsHandler::mainThreadHandler->detach();
	}

	int ThreadRequestsHandler::GetStatus(){
		return ThreadRequestsHandler::isWorking;
	}

	void ThreadRequestsHandler::StopWorking(){
		ThreadRequestsHandler::isWorking = false;
	}
