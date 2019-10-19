#include "MainInterfaces.h"
#include "NetSocketWorker.h"
#include <cstring>
#include <iostream>

	void NetSocketWorker::GetAddr(sockaddr_in &addr,  ClientAddr* caddr){
		addr.sin_family = AF_INET;
		addr.sin_port = htons(caddr->port);
		struct hostent *server;
		server = gethostbyname(caddr->ip);
		//bcopy((char *)server->h_addr, (char *)&addr.sin_addr.s_addr, server->h_length);
		std::memmove((char*)&addr.sin_addr.s_addr, (char *)server->h_addr, server->h_length);
	}


	int NetSocketWorker::GetNewSocketId() {
		return socket(AF_INET, SOCK_STREAM, 0);
	}


	int NetSocketWorker::Recieve(int socketId, char* buff, int size){
		return recv(socketId, buff, size, 0);
	}
	void NetSocketWorker::Send(int socketId, char* buff, int size){
		send(socketId, buff, size, 0);
	}


	bool NetSocketWorker::Bind(int socketId,  ClientAddr* addr){
		struct sockaddr_in saddr;
		NetSocketWorker::GetAddr(saddr, addr);
		return bind(socketId, (struct sockaddr *)&saddr, sizeof(saddr))<0;
	}
	void NetSocketWorker::Listen(int socketId, int count = 1){
		listen(socketId, count);
	}
	int NetSocketWorker::Accept(int socketId){
		return accept(socketId, NULL, NULL);
	}
	int NetSocketWorker::ConnectTo(int socketId,  ClientAddr* addr){
		struct sockaddr_in saddr;
		NetSocketWorker::GetAddr(saddr, addr);
		return connect(socketId, (struct sockaddr *)&saddr, sizeof(saddr));
	}
