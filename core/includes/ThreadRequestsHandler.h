/*
 *  Author: Ivan Khodyrev
 */

#ifndef ThreadRequestsHandler_H
#define ThreadRequestsHandler_H

namespace P2P_Network{

	class Thread_Requests_Handler: public I_Requests_Handler{
	private:
		I_Socket_Worker *socket_worker;
		I_Data_Worker *data_worker;
		bool is_working = false;
	public:
		void set_Workers(I_Socket_Worker *socket_worker, I_Command_Interpreter *cmd_interpeter);

		void start_Working(Client_Addr* addr);

		int get_Status();

		void stop_Working();
	};

}

#endif