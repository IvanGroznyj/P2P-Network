/*
 *  Author: Ivan Khodyrev
 */

#ifndef MainInterfaces_H
#define MainInterfaces_H

namespace P2P_Network{

	struct Client_Addr{
		Client_Addr();
		Client_Addr(char* addr);
		Client_Addr(char* ip, int port);

		bool operator==(const Client_Addr& addr);
		char* to_str();

		char* ip;
		int port;
	};

	class I_Socket_Worker{
	public:
		virtual int get_New_Socket_Id() =0;

		virtual int recieve_buffer(int socket_id, char* buff, int size)=0;
		virtual void send_buffer(int socket_id, const char* buff, int size)=0;

		virtual bool bind_socket(int socket_id, Client_Addr* addr)=0;
		virtual void listen_sockets(int socket_id, int count)=0;
		virtual int accept_socket(int socket_id)=0;
		virtual int connect_To(int socket_id, Client_Addr* addr)=0;
		virtual void close_socket(int socket_id)=0;
	};

	class I_Data_Worker{
	public:
		virtual char* get_File(const char* hash)=0;
		virtual char* get_File_By_Name(const char* name)=0;
		virtual void append_To_File_By_Name(const char* name, const char* text)=0;
		virtual unsigned long int get_Hash(const char* path)=0;
		virtual char* add_File(const char* path)=0;
	};

	class I_Requests_Handler{
	public:
		virtual void start_Working(Client_Addr* addr)=0;
		virtual int get_Status()=0;
		virtual void stop_Working()=0;
	};

}

#endif