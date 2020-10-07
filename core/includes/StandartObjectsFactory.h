/*
 *  Author: Ivan Khodyrev
 */

#ifndef Standart_Objects_Factory_H
#define Standart_Objects_Factory_H

#include "CoreObjectsFactory.h"

namespace P2P_Network{

	class Standart_Objects_Factory: public Core_Objects_Factory {
	public:
		I_Socket_Worker* get_Socket_Worker();
		I_Requests_Handler* get_Requests_Handler();
		I_Data_Worker* get_Data_Worker();
		Client* get_Client();
		I_Command_Interpreter* get_Command_Interpreter();
	};

}

#endif