#include "MainInterfaces.h"

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sstream>

using namespace std;
using namespace P2P_Network;

Client_Addr::Client_Addr(){
	ip = "127.0.0.1";
	port = 9090;
}

Client_Addr::Client_Addr(string addr){
	int pos = addr.find(":");
	Client_Addr::ip = addr.substr(0, pos);
	Client_Addr::port = atoi(addr.substr(pos+1).c_str());
}

Client_Addr::Client_Addr(string ip, int port){
	Client_Addr::ip = ip;
	Client_Addr::port = port;
}

bool Client_Addr::operator==(const Client_Addr& addr){
	return (ip == addr.ip) && (port == addr.port);
}

string Client_Addr::to_str(){
	stringstream result_str;
	result_str << Client_Addr::ip;
	result_str << ":";
	result_str << Client_Addr::port;
	return result_str.str();
}