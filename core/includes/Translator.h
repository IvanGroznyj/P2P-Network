/*
 *  Author: Ivan Khodyrev
 */

#ifndef Translator_H
#define Translator_H

#include "Commands.h"

namespace P2P_Network{

	class Translator {
	private:
		const static char separator = '|';
	public:
		const char* command_To_Text(Command *cmd);
		Command* text_To_Command(const char* cmd_str);
	};

}	

#endif