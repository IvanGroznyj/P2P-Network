/*
 *  Author: Ivan Khodyrev
 */

#ifndef Client_H
#define Client_H

#include "MainInterfaces.h"
#include <vector>

namespace P2P_Network{

	class Client {	
	private:
		I_Socket_Worker *sworker;
		I_Requests_Handler *handler;
		I_Data_Worker *dworker;
		Client_Addr* addr;
		char *net_time;
		std::vector<Client_Addr*> *addrs;
	public:
		Client();
		void bind(Client_Addr* addr);
		void start_Listen();
		void stop_Listen();
		char* get_Answer(Client_Addr* addr, const char* msg, int msg_size);
		void set_Socket_Worker(I_Socket_Worker* sw);
		void set_Data_Worker(I_Data_Worker* dw);
		void set_Requests_Handler(I_Requests_Handler* rh);
		const char* get_Network_Time();
		void update_Global_Time();
		void update_Node_Addrs_In_Network();
		std::vector<Client_Addr*>* get_Node_Addrs_In_Network();
	};

}

#endif