/*
 *  Author: Ivan Khodyrev
 */
#include "MainInterfaces.h"
#include "NetSocketWorker.h"
#include <cstring>
#include <iostream>
#include <unistd.h>
using namespace std;

void NetSocketWorker::ConvertAddr(sockaddr_in &output_addr,  ClientAddr* client_addr){
	output_addr.sin_family = AF_INET;
	output_addr.sin_port = htons(client_addr->port);
	struct hostent *server;
	server = gethostbyname(client_addr->ip);
	memmove((char*)&output_addr.sin_addr.s_addr, (char*)server->h_addr, server->h_length);
}

int NetSocketWorker::GetNewSocketId() {
	return socket(AF_INET, SOCK_STREAM, 0);
}

int NetSocketWorker::Recieve(int socket_id, char* buff, int size){
	try{
		return recv(socket_id, buff, size, 0);
	}catch(...){
		return -1;
	}
}

void NetSocketWorker::Send(int socket_id, const char* buff, int size){
	try{
		send(socket_id, buff, size, IPPROTO_TCP);
	}catch(...){}
}

bool NetSocketWorker::Bind(int socket_id,  ClientAddr* addr){
	struct sockaddr_in connection_addr;
	NetSocketWorker::ConvertAddr(connection_addr, addr);
	int reuse = 1;
	setsockopt(socket_id, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse));
	return bind(socket_id, (struct sockaddr *)&connection_addr, sizeof(connection_addr))<0;
}

void NetSocketWorker::Listen(int socket_id, int count = 1){
	listen(socket_id, count);
}

int NetSocketWorker::Accept(int socket_id){
	return accept(socket_id, NULL, NULL);
}

int NetSocketWorker::ConnectTo(int socket_id,  ClientAddr* addr){
	struct sockaddr_in connection_addr;
	NetSocketWorker::ConvertAddr(connection_addr, addr);
	return connect(socket_id, (struct sockaddr *)&connection_addr, sizeof(connection_addr));
}

void NetSocketWorker::Close(int socket_id){
	close(socket_id);
}
