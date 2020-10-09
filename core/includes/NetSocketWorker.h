/*
 *  Author: Ivan Khodyrev
 */
#ifndef NetSocketWorker_H
#define NetSocketWorker_H

#ifdef __linux__
    #include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <netdb.h>
#elif _WIN32
	#include <winsock2.h>
	#include <ws2tcpip.h>
#endif

#include "MainInterfaces.h"

namespace P2P_Network{

	class Net_Socket_Worker: public I_Socket_Worker{
	private:
		void convert_Addr(sockaddr_in &addr, Client_Addr* client_addr);
	public:
		int get_New_Socket_Id();
		
		string recieve_buffer(int socket_id);
		void send_buffer(int socket_id, string buff);
		
		bool bind_socket(int socket_id,  Client_Addr* addr);
		void listen_sockets(int socket_id, int count);
		int accept_socket(int socket_id);
		int connect_To(int socket_id,  Client_Addr* addr);
		void close_socket(int socket_id);
	};	

}

#endif