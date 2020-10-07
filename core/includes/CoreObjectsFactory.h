#ifndef Core_Objects_Factory_H
#define Core_Objects_Factory_H

#include "MainInterfaces.h"
#include "Client.h"
#include "CommandInterpreter.h"

namespace P2P_Network{

	class Core_Objects_Factory{
	public:
		virtual I_Socket_Worker* get_Socket_Worker()=0;
		virtual I_Requests_Handler* get_Requests_Handler()=0;
		virtual I_Data_Worker* get_Data_Worker()=0;
		virtual Client* get_Client()=0;
		virtual I_Command_Interpreter* get_Command_Interpreter()=0;
	};

}

#endif