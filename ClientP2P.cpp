using namespace std;

#include <cstdio>
#include <iostream>
#include <unistd.h>
#include "MainInterfaces.h"
#include "ClientP2P.h"
#include "Commands.h"
#include "NatPMP.h"
#include <cstring>

#define ANSWER_BODY_START_ROW 11

P2PClient::P2PClient(){
	P2PClient::addr = new ClientAddr((char *)"127.0.0.1", 9091);
	P2PClient::handler = nullptr;
	P2PClient::sworker = nullptr;
	P2PClient::dworker = nullptr;
	P2PClient::net_time = "00:00:00";
	P2PClient::addrs = new std::vector<ClientAddr*>();
}

void P2PClient::BindClient(ClientAddr* addr){
	P2PClient::addr->ip = addr->ip;
	P2PClient::addr->port = addr->port;
}

void P2PClient::StartListen(){
	ClientAddr *addr = new ClientAddr("igp2p.000webhostapp.com", 80);

	std::string request_str = "GET /?cmd=addMe&ip=";
	request_str+=P2PClient::addr->ip;
	request_str+="&port=";
	request_str+=to_string(P2PClient::addr->port);
	request_str+=" HTTP/1.1\r\nHost: igp2p.000webhostapp.com\r\n\r\n";

	P2PClient::GetAnswer(addr, (char*)request_str.c_str(), request_str.size());

	NatPMP::PortForwarding(NatPMP::TCP_CODE, P2PClient::addr->port, P2PClient::addr->port, 3600);

	P2PClient::handler->StartWorking(P2PClient::addr);
};

void P2PClient::StopListen(){
	P2PClient::handler->StopWorking();
	NatPMP::PortForwarding(NatPMP::TCP_CODE, P2PClient::addr->port, P2PClient::addr->port, 0);
};

char* P2PClient::GetAnswer(ClientAddr *addr, char* msg, int msg_size){
	int sock = P2PClient::sworker->GetNewSocketId();
	if(sock < 0) return "socket error";
	if(P2PClient::sworker->ConnectTo(sock, addr)<0) return "connection error";
	P2PClient::sworker->Send(sock, msg, msg_size+1);

	string result_str = "";
	int bytes_read;
	char *recieve_buffer = new char[1024];
	bytes_read = P2PClient::sworker->Recieve(sock, recieve_buffer, 1024);
	while(bytes_read>0){
		result_str += recieve_buffer;
		delete[] recieve_buffer;
		recieve_buffer = new char[1024];
		bytes_read = P2PClient::sworker->Recieve(sock, recieve_buffer, 1024);
	}
	recieve_buffer = new char[result_str.size()+1];
	strcpy(recieve_buffer, result_str.c_str());
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

char* P2PClient::GetNetworkTime(){
	return P2PClient::net_time;
}

std::vector<ClientAddr*>* P2PClient::GetNodeAddrsInNetwork(){
	return P2PClient::addrs;
}

void P2PClient::UpdateGlobalTime(){
	ClientAddr *addr = new ClientAddr("igp2p.000webhostapp.com", 80);
	char *request_str = "GET /?cmd=getTime HTTP/1.1\r\nHost: igp2p.000webhostapp.com\r\n\r\n";

	char *answer_body = P2PClient::GetAnswer(addr, request_str, strlen(request_str));

	int current_row_number = 0;
	std::string result_str = "";
	while (*answer_body!='\0'){
		if(*answer_body=='\n'){
			current_row_number++;
		}else{
			if(current_row_number==ANSWER_BODY_START_ROW) result_str += *answer_body;
		}
		if(current_row_number>ANSWER_BODY_START_ROW) break;
		answer_body++;
	}
	P2PClient::net_time = new char[result_str.size()+1];
	strcpy(P2PClient::net_time, (char*)result_str.c_str());
}

void P2PClient::UpdateNodeAddrsInNetwork(){
	ClientAddr *addr = new ClientAddr("igp2p.000webhostapp.com", 80);
	char *request_str = "GET /?cmd=getAddrs HTTP/1.1\r\nHost: igp2p.000webhostapp.com\r\n\r\n";

	char *answer_body = P2PClient::GetAnswer(addr, request_str, strlen(request_str));

	P2PClient::addrs->clear();
	std::string ip = "";
	std::string port = "";
	int current_row_number = 0;
	char *tmp_buffer;
	bool is_ip_reading = true;
	while (*answer_body!='\0'){
		if(*answer_body=='\n'){
			current_row_number++;
			if (current_row_number>=ANSWER_BODY_START_ROW+1) {
				tmp_buffer = new char[ip.size()+1];
				strcpy(tmp_buffer, ip.c_str());
				addr = new ClientAddr(tmp_buffer, std::atoi(port.c_str()));
				P2PClient::addrs->push_back(addr);

				is_ip_reading = true;
				port = "";
				ip = "";
			}
		}else{
			if(current_row_number>=ANSWER_BODY_START_ROW) {
				if(*answer_body == '-') {
					break;
				}
				if(*answer_body==':') {
					is_ip_reading = false;
				}else
				if (is_ip_reading){
					ip += *answer_body;
				}else{
					port += *answer_body;
				}
			}
		}
		answer_body++;
	}
}
