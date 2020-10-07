#include "MainInterfaces.h"

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sstream>

using namespace std;
using namespace P2P_Network;

Client_Addr::Client_Addr(){
	ip = 0;
	port = 9090;
}

Client_Addr::Client_Addr(char* addr){
	stringstream ip_str, port_str;

	char* cur_char = addr;
	while(*cur_char != ':'){
		ip_str << *cur_char;
		cur_char++;
	}
	Client_Addr::ip = new char[ip_str.str().size()+1];
	strcpy(Client_Addr::ip, ip_str.str().c_str());

	cur_char++;
	while(*cur_char != '\0'){
		port_str << *cur_char;
		cur_char++;
	}
	Client_Addr::port = atoi(port_str.str().c_str());
}

Client_Addr::Client_Addr(char* ip, int port){
	Client_Addr::ip = ip;
	Client_Addr::port = port;
}

bool Client_Addr::operator==(const Client_Addr& addr){
	return ip == addr.ip && port == addr.port;
}

char* Client_Addr::to_str(){
	stringstream result_str;
	result_str << Client_Addr::ip;
	result_str << ":";
	result_str << Client_Addr::port;

	char* result = new char[result_str.str().size()+1];
	strcpy(result, result_str.str().c_str());
	return result;
}