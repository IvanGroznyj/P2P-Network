/*
 *  Author: Ivan Khodyrev
 */
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include "MainInterfaces.h"
#include "Client.h"
#include "Commands.h"
#include "NatPMP.h"
#include <cstring>
#include <sstream>
#include <ctime>

using namespace std;
using namespace P2P_Network;

Client::Client(){
	Client::addr = new Client_Addr("127.0.0.1", 9091);
	Client::handler = nullptr;
	Client::sworker = nullptr;
	Client::dworker = nullptr;
	Client::net_time = "00:00:00";
	Client::addrs = new vector<Client_Addr*>();
}

void Client::bind(Client_Addr* addr){
	Client::addr->ip = addr->ip;
	Client::addr->port = addr->port;
}

void Client::start_Listen(){
	Nat_PMP::port_Forwarding(Nat_PMP::TCP_CODE, Client::addr->port, Client::addr->port, 3600);

	Client::handler->start_Working(Client::addr);
	// TODO: reqest addrs
	Client::update_Node_Addrs_In_Network();
};

void Client::stop_Listen(){
	Client::handler->stop_Working();
	Nat_PMP::port_Forwarding(Nat_PMP::TCP_CODE, Client::addr->port, Client::addr->port, 0);
};

char* Client::get_Answer(Client_Addr *addr, const char* msg, int msg_size){
	int sock = Client::sworker->get_New_Socket_Id();
	if(sock < 0) return "socket error";
	if(Client::sworker->connect_To(sock, addr)<0) return "connection error";
	Client::sworker->send_buffer(sock, msg, msg_size+1);

	stringstream result_str;
	result_str << "";
	int bytes_read = 1024;
	char *recieve_buffer;

	while(bytes_read==1024){
		recieve_buffer = new char[1024];
		bytes_read = sworker->recieve_buffer(sock, recieve_buffer, 1024);
		result_str << recieve_buffer;
		delete[] recieve_buffer;
	}

	recieve_buffer = new char[result_str.str().size()+1];
	strcpy(recieve_buffer, result_str.str().c_str());
	return recieve_buffer;
}

void Client::set_Socket_Worker(I_Socket_Worker* sw){
	Client::sworker = sw;
}
void Client::set_Data_Worker(I_Data_Worker* dw){
	Client::dworker = dw;
}
void Client::set_Requests_Handler(I_Requests_Handler* rh){
	Client::handler = rh;
}

const char* Client::get_Network_Time(){
	return Client::net_time;
}

vector<Client_Addr*>* Client::get_Node_Addrs_In_Network(){
	return Client::addrs;
}

void Client::update_Global_Time(){
	time_t now = time(0);
	tm *gmtm = gmtime(&now);

	stringstream result_time;
	result_time << 1900 + gmtm->tm_year << "-";
	result_time << 1 + gmtm->tm_mon << "-";
	result_time << gmtm->tm_mday << "_";
	result_time << 1 + gmtm->tm_hour << ":";
	result_time << 1 + gmtm->tm_min << ":";
	result_time << 1 + gmtm->tm_sec;

	Client::net_time = new char[result_time.str().size()+1];
	strcpy(Client::net_time, result_time.str().c_str());
}

void Client::update_Node_Addrs_In_Network(){
	Client::addrs->clear();
	Client::addrs->push_back(new Client_Addr("127.0.0.1", 9094));
	Client::addrs->push_back(new Client_Addr("127.0.0.1", 9091));
	// TODO: add requests for other
}
