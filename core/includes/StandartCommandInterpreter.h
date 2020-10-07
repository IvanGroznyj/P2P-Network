/*
 *  Author: Ivan Khodyrev
 */

#ifndef StadnartCommandInterpreter_H
#define StadnartCommandInterpreter_H

#include "CommandInterpreter.h"

namespace P2P_Network{

	class Stadnart_Command_Interpreter: public I_Command_Interpreter{
	private:
		int sock_id;
		I_Data_Worker *data_worker;
		const char* virtual_dir = "virtualdata/";
	public:
		void set_Data_Worker(I_Data_Worker *data_worker);
		char* do_Command(Command *cmd);
	};

}

#endif