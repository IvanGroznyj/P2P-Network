/*
 *  Author: Ivan Khodyrev
 */

#ifndef CommandInterpreter_H
#define CommandInterpreter_H

#include "Translator.h"

namespace P2P_Network{

	class I_Command_Interpreter {
	public:
		virtual void set_Data_Worker(I_Data_Worker *dw)=0;
		virtual char* do_Command(Command *cmd)=0;
	};

}

#endif