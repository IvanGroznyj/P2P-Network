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

	Client::update_Node_Addrs_In_Network();
};

void Client::stop_Listen(){
	Client::handler->stop_Working();
	Nat_PMP::port_Forwarding(Nat_PMP::TCP_CODE, Client::addr->port, Client::addr->port, 0);
};

Response_Body Client::get_Answer(Client_Addr *addr, string msg){
	int sock = Client::sworker->get_New_Socket_Id();
	if(sock < 0) return Response_Body(Socket_Error, "");
	if(Client::sworker->connect_To(sock, addr)<0) return Response_Body(Connection_Error, "");
	Client::sworker->send_buffer(sock, msg);
	return Response_Body(OK, sworker->recieve_buffer(sock));
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

string Client::get_Network_Time(){
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

bool in_Addrs(Client_Addr* addr, vector<Client_Addr*> *addrs);
vector<Client_Addr*>* get_Clients_From_Str(string str);

void Client::update_Node_Addrs_In_Network(){
	Client::addrs->clear();
	Client::addrs->push_back(Client::addr);
	Client_Addr* tmp_addr;

	vector<Client_Addr*> *new_addrs = new vector<Client_Addr*>();
	vector<Client_Addr*> *tmp_addrs;
	int i=0;
	string tmp_str;
	while (i<Client::addrs->size()){
		string request_cmd = Get_Virtual_File_Command("ips").to_str();
		Response_Body response = Client::get_Answer(Client::addrs->at(i), request_cmd);
		if (response != OK){
			i++;
			continue;
		}
		tmp_addrs = get_Clients_From_Str(response.response_text);
		for(int j=0; j < tmp_addrs->size(); j++){
			if(!in_Addrs(tmp_addrs->at(j), Client::addrs)){
				new_addrs->push_back(tmp_addrs->at(j));
				Client::addrs->push_back(tmp_addrs->at(j));
			}
		}		
		i++;
	}

	stringstream addrs_list;
	for(int i=0; i<new_addrs->size(); i++){
		addrs_list<<new_addrs->at(i)->to_str()<<"\n";
	}

	string request_cmd = Write_To_Virtual_File_Command("ips", addrs_list.str()).to_str();
	Client::get_Answer(Client::addr, request_cmd);
}

vector<Client_Addr*>* get_Clients_From_Str(string str){
	int start_pos, end_pos;
	start_pos = str.find("\n");
	vector<Client_Addr*> *new_addrs = new vector<Client_Addr*>();
	Client_Addr* tmp_addr;
	string tmp_str;
	if (start_pos != string::npos){
		start_pos = 0;
		end_pos = str.find("\n", start_pos);
		while(end_pos != string::npos){
			tmp_addr = new Client_Addr(str.substr(start_pos, end_pos - start_pos));
			new_addrs->push_back(tmp_addr);
			start_pos = end_pos + 1;
			end_pos = str.find("\n", start_pos);		
		}
		tmp_str = str.substr(start_pos);
		if (tmp_str.size() > 0){
			tmp_addr = new Client_Addr(tmp_str);
			new_addrs->push_back(tmp_addr);
		}			
	}
	return new_addrs;
}

bool in_Addrs(Client_Addr* addr, vector<Client_Addr*> *addrs){
	cout<<"===="<<endl;
	for(int i=0; i<addrs->size(); i++){
		cout<<addr->to_str() << " - "<< addrs->at(i)->to_str() << " = "<< (*addr == *(addrs->at(i)))<<endl;
		if(*addr == *(addrs->at(i))) return true;
	}
	return false;
}
