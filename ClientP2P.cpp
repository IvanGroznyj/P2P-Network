using namespace std;

#include <cstdio>
#include <iostream>
#include <unistd.h>
#include "MainInterfaces.h"
#include "ClientP2P.h"
#include "Commands.h"
#include <cstring>

P2PClient::P2PClient(){
	P2PClient::addr = new ClientAddr((char *)"127.0.0.1", 9091);
	P2PClient::handler = nullptr;
	P2PClient::sworker = nullptr;
	P2PClient::dworker = nullptr;
	P2PClient::netTime = "00:00:00";
}

void P2PClient::BindClient(ClientAddr* addr){
	P2PClient::addr->ip = addr->ip;
	P2PClient::addr->port = addr->port;
}

void P2PClient::StartListen(){
	P2PClient::handler->StartWorking(P2PClient::addr);
};

void P2PClient::StopListen(){
	P2PClient::handler->StopWorking();
};

char* P2PClient::GetAnswer(ClientAddr *addr, char* msg, int msgsize){
	int sock = P2PClient::sworker->GetNewSocketId();
	if(sock < 0)
	{
		perror("socket");
		exit(1);
	}
	if(P2PClient::sworker->ConnectTo(sock, addr)<0)
	{
		perror("connect");
		exit(2);
	}
	P2PClient::sworker->Send(sock, msg, msgsize+1);
	string resStr = "";
	char *buf;
	int bytes_read;
	while(true){
		buf = new char[1024];
		bytes_read = P2PClient::sworker->Recieve(sock, buf, 1024);
		resStr += buf;
		delete[] buf;
		if(bytes_read<1024) break;
	}
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

char* P2PClient::GetNetworkTime(){
	return P2PClient::netTime;
}

std::vector<ClientAddr*>* P2PClient::GetNodeAddrsInNetwork(){
	std::vector<ClientAddr*> *addrs = new std::vector<ClientAddr*>();
	addrs->push_back(P2PClient::addr);
	return addrs;
}
