/*
 *  Author: Ivan Khodyrev
 */
#include "MainInterfaces.h"
#include "NetSocketWorker.h"
#include <cstring>
#include <iostream>
#include <unistd.h>
using namespace std;

#ifdef _WIN32
	WSADATA wsaData;
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif


void NetSocketWorker::ConvertAddr(sockaddr_in &output_addr,  ClientAddr* client_addr){
	output_addr.sin_family = AF_INET;
	output_addr.sin_port = htons(client_addr->port);
	#ifdef __linux__
		struct hostent *server;
		server = gethostbyname(client_addr->ip);
		memmove((char*)&output_addr.sin_addr.s_addr, (char*)server->h_addr, server->h_length);
	#elif _WIN32
		output_addr.sin_addr.s_addr = inet_addr(client_addr->ip);
	#endif
}

int NetSocketWorker::GetNewSocketId() {
	return socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

int NetSocketWorker::Recieve(int socket_id, char* buff, int size){
	return recv(socket_id, buff, size, 0);
}

void NetSocketWorker::Send(int socket_id, const char* buff, int size){
	try{
		send(socket_id, buff, size, 0);
	}catch(...){}
}

bool NetSocketWorker::Bind(int socket_id,  ClientAddr* addr){
	struct sockaddr_in connection_addr;
	NetSocketWorker::ConvertAddr(connection_addr, addr);
	const char reuse = 1;
	#ifdef __linux__
		setsockopt(socket_id, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse));
	#elif _WIN32
		setsockopt(socket_id, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
	#endif	
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
