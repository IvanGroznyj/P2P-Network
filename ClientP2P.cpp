using namespace std;

#include <cstdio>
#include <iostream>
#include <unistd.h>
#include "MainInterfaces.h"
#include "ClientP2P.h"
#include <cstring>

P2PClient::P2PClient(){
	P2PClient::ip = (char *)"127.0.0.1";
	P2PClient::port = 9090;
	P2PClient::handler = nullptr;
	P2PClient::sworker = nullptr;
	P2PClient::dworker = nullptr;
}

void P2PClient::BindClient(char* ip, int port){
	P2PClient::ip = ip;
	P2PClient::port = port;
}

/*void P2PClient::Build(StandartBuilder *builder){
	P2PClient::sworker = builder->BuildSocketWorker();
	P2PClient::handler = builder->BuildRequestsHandler();
	P2PClient::dworker = builder->BuildDataWorker();
}*/

void P2PClient::StartListen(){
	P2PClient::handler->StartWorking(P2PClient::ip, P2PClient::port);
};

void P2PClient::StopListen(){
	P2PClient::handler->StopWorking();
};

char* P2PClient::GetAnswer(char *ip, int port, char* msg, int msgsize){
	int sock = P2PClient::sworker->GetNewSocketId();
	if(sock < 0)
	{
		perror("socket");
		exit(1);
	}

	if(P2PClient::sworker->ConnectTo(sock, ip, port)<0)
	{
		perror("connect");
		exit(2);
	}
	//cout<<"<> "<<msg<<endl;
	P2PClient::sworker->Send(sock, msg, msgsize);
	string resStr = "";
	char *buf;
	char *tmpbuf;
	int bytes_read;
	while(true){
		buf = new char[1024];
		bytes_read = P2PClient::sworker->Recieve(sock, buf, 1024);
		tmpbuf = new char[bytes_read+1];
		strncpy(tmpbuf, buf, bytes_read+1);
		resStr += tmpbuf;
		delete[] tmpbuf;
		delete[] buf;
		//cout<<">> "<<resStr<<endl;
		if(bytes_read<1024) break;
	}
	//cout<<"> "<<resStr<<endl;
	buf = new char[resStr.size()+1];
	strcpy(buf, resStr.c_str());
	return buf;
}

void P2PClient::SetSocketWorker(ISocketWorker* sw){
	P2PClient::sworker = sw;
}
void P2PClient::SetDataWorker(IDataWorker* dw){
	P2PClient::dworker = dw;
}
void P2PClient::SetRequestsHandler(IRequestsHandler* rh){
	P2PClient::handler = rh;
}
