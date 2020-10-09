/*
 *  Author: Ivan Khodyrev
 */

#ifndef MainInterfaces_H
#define MainInterfaces_H

#include <string>
using namespace std;

namespace P2P_Network{

	struct Client_Addr{
		Client_Addr();
		Client_Addr(string addr);
		Client_Addr(string ip, int port);

		bool operator==(const Client_Addr& addr);
		string to_str();

		string ip;
		int port;
	};

	class I_Socket_Worker{
	public:
		virtual int get_New_Socket_Id() =0;

		virtual string recieve_buffer(int socket_id)=0;
		virtual void send_buffer(int socket_id, string buff)=0;

		virtual bool bind_socket(int socket_id, Client_Addr* addr)=0;
		virtual void listen_sockets(int socket_id, int count)=0;
		virtual int accept_socket(int socket_id)=0;
		virtual int connect_To(int socket_id, Client_Addr* addr)=0;
		virtual void close_socket(int socket_id)=0;
	};

	enum Write_Modes{Rewrite_Mode=1, Append_Mode};

	class I_Data_Worker{
	public:
		virtual string get_File(string hash)=0;
		virtual string get_File_By_Name(string name)=0;
		virtual void write_To_File_By_Name(string name, string text, Write_Modes write_mode)=0;
		virtual unsigned long int get_Hash(string path)=0;
		virtual string add_File(string path)=0;
	};

	class I_Requests_Handler{
	public:
		virtual void start_Working(Client_Addr* addr)=0;
		virtual int get_Status()=0;
		virtual void stop_Working()=0;
	};

}

#endif