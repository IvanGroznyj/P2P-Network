/*
 *  Author: Ivan Khodyrev
 */
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include "MainInterfaces.h"
#include "ClientP2P.h"
#include "Commands.h"
#include "NatPMP.h"
#include <cstring>
#include <sstream>
#include <ctime>

using namespace std;

#define ANSWER_BODY_START_ROW 11
#define MAIN_SERVER_ADDR "igp2p.000webhostapp.com"

P2PClient::P2PClient(){
	P2PClient::addr = new ClientAddr("127.0.0.1", 9091);
	P2PClient::handler = nullptr;
	P2PClient::sworker = nullptr;
	P2PClient::dworker = nullptr;
	P2PClient::net_time = "00:00:00";
	P2PClient::addrs = new vector<ClientAddr*>();
}

void P2PClient::BindClient(ClientAddr* addr){
	P2PClient::addr->ip = addr->ip;
	P2PClient::addr->port = addr->port;
}

void P2PClient::StartListen(){
//	ClientAddr *addr = new ClientAddr(MAIN_SERVER_ADDR, 80);
//
//	stringstream request_str;
//	request_str << "GET /?cmd=addMe&ip=";
//	request_str << P2PClient::addr->ip;
//	request_str << "&port=";
//	request_str << to_string(P2PClient::addr->port);
//	request_str << " HTTP/1.1\r\nHost: ";
//	request_str << MAIN_SERVER_ADDR;
//	request_str << "\r\n\r\n";
//
//	P2PClient::GetAnswer(addr, request_str.str().c_str(), request_str.str().size());
//	delete addr;

	NatPMP::PortForwarding(NatPMP::TCP_CODE, P2PClient::addr->port, P2PClient::addr->port, 3600);

	P2PClient::handler->StartWorking(P2PClient::addr);
};

void P2PClient::StopListen(){
	P2PClient::handler->StopWorking();
	NatPMP::PortForwarding(NatPMP::TCP_CODE, P2PClient::addr->port, P2PClient::addr->port, 0);
};

char* P2PClient::GetAnswer(ClientAddr *addr, const char* msg, int msg_size){
	int sock = P2PClient::sworker->GetNewSocketId();
	if(sock < 0) return "socket error";
	if(P2PClient::sworker->ConnectTo(sock, addr)<0) return "connection error";
	P2PClient::sworker->Send(sock, msg, msg_size+1);

	stringstream result_str;
	result_str << "";
	int bytes_read = 1024;
	char *recieve_buffer;

	while(bytes_read==1024){
		recieve_buffer = new char[1024];
		bytes_read = sworker->Recieve(sock, recieve_buffer, 1024);
		result_str << recieve_buffer;
		delete[] recieve_buffer;
	}

	recieve_buffer = new char[result_str.str().size()+1];
	strcpy(recieve_buffer, result_str.str().c_str());
	return recieve_buffer;
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

const char* P2PClient::GetNetworkTime(){
	return P2PClient::net_time;
}

vector<ClientAddr*>* P2PClient::GetNodeAddrsInNetwork(){
	return P2PClient::addrs;
}

void P2PClient::UpdateGlobalTime(){
	time_t now = time(0);
	tm *gmtm = gmtime(&now);

	stringstream result_time;
	result_time << 1900 + gmtm->tm_year << "-";
	result_time << 1 + gmtm->tm_mon << "-";
	result_time << gmtm->tm_mday << "_";
	result_time << 1 + gmtm->tm_hour << ":";
	result_time << 1 + gmtm->tm_min << ":";
	result_time << 1 + gmtm->tm_sec;

	P2PClient::net_time = new char[result_time.str().size()+1];
	strcpy(P2PClient::net_time, result_time.str().c_str());
}

void P2PClient::UpdateNodeAddrsInNetwork(){
	P2PClient::addrs->clear();
	P2PClient::addrs->push_back(new ClientAddr("127.0.0.1", 9094));
	P2PClient::addrs->push_back(new ClientAddr("127.0.0.1", 9091));
	// TODO: add requests for other
}
