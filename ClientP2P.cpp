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
	P2PClient::addrs = new std::vector<ClientAddr*>();
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
	return addrs;
}

void P2PClient::UpdateGlobalTime(){
	ClientAddr *addr = new ClientAddr("igp2p.000webhostapp.com", 80);
	char *req = "GET /?cmd=getTime HTTP/1.1\r\nHost: igp2p.000webhostapp.com\r\n\r\n";
	char *p = P2PClient::GetAnswer(addr, req, strlen(req));
	int k = 0;
	std::string res = "";
	while (*p!='\0'){
		if(*p=='\n'){
			k++;
		}else{
			if(k==11) res += *p;
		}
		if(k>11) break;
		p++;
	}
	P2PClient::netTime = new char[res.size()+1];
	strcpy(P2PClient::netTime, (char*)res.c_str());
}

void P2PClient::UpdateNodeAddrsInNetwork(){
	ClientAddr *addr = new ClientAddr("igp2p.000webhostapp.com", 80);
	char *req = "GET /?cmd=getAddrs HTTP/1.1\r\nHost: igp2p.000webhostapp.com\r\n\r\n";
	char *p = P2PClient::GetAnswer(addr, req, strlen(req));
	std::vector<ClientAddr*> *newaddrs = new std::vector<ClientAddr*>();
			std::string tmp = "";
			std::string ip = "";
			std::string port = "";
			int k = 0;
			char *tmpbuf;
			bool flag = true;
			while (*p!='\0'){
				if(*p=='\n'){
							k++;
							if (k>=12) {
								tmpbuf = new char[ip.size()+1];
								strcpy(tmpbuf, ip.c_str());
								newaddrs->push_back(new ClientAddr(tmpbuf, std::atoi(port.c_str())));
								flag = true;
								port = "";
								ip = "";
								tmp = "";
							}
						}else{
							if(k>=11) {
								//tmp += *p;
								if(*p == '.' && *(p-1)=='\n') break;
								if(*p==':') {
									flag = false;
									p++;
								}
								if (flag){
									ip += *p;
								}else{
									port += *p;
								}
							}
						}
						p++;
			}
	/*for (int i=0; i<newaddrs->size(); i++){
		cout<<newaddrs->at(i)->ip<<":"<<newaddrs->at(i)->port<<endl;
	}*/
	P2PClient::addrs->clear();
	P2PClient::addrs = newaddrs;
}
