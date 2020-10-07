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


void P2P_Network::Net_Socket_Worker::convert_Addr(sockaddr_in &output_addr,  Client_Addr* client_addr){
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

int P2P_Network::Net_Socket_Worker::get_New_Socket_Id() {
	return socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

int P2P_Network::Net_Socket_Worker::recieve_buffer(int socket_id, char* buff, int size){
	return recv(socket_id, buff, size, 0);
}

void P2P_Network::Net_Socket_Worker::send_buffer(int socket_id, const char* buff, int size){
	try{
		send(socket_id, buff, size, 0);
	}catch(...){}
}

bool P2P_Network::Net_Socket_Worker::bind_socket(int socket_id,  Client_Addr* addr){
	struct sockaddr_in connection_addr;
	P2P_Network::Net_Socket_Worker::convert_Addr(connection_addr, addr);
	const char reuse = 1;
	#ifdef __linux__
		setsockopt(socket_id, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse));
	#elif _WIN32
		setsockopt(socket_id, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
	#endif	
	return bind(socket_id, (struct sockaddr *)&connection_addr, sizeof(connection_addr))<0;
}

void P2P_Network::Net_Socket_Worker::listen_sockets(int socket_id, int count = 1){
	listen(socket_id, count);
}

int P2P_Network::Net_Socket_Worker::accept_socket(int socket_id){
	return accept(socket_id, NULL, NULL);
}

int P2P_Network::Net_Socket_Worker::connect_To(int socket_id,  Client_Addr* addr){
	struct sockaddr_in connection_addr;
	P2P_Network::Net_Socket_Worker::convert_Addr(connection_addr, addr);
	return connect(socket_id, (struct sockaddr *)&connection_addr, sizeof(connection_addr));
}

void P2P_Network::Net_Socket_Worker::close_socket(int socket_id){
	close(socket_id);
}
