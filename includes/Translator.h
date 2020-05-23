/*
 *  Author: Ivan Khodyrev
 */
#include "Commands.h"

class Translator {
private:
	const static char separator = '|';
public:
	const char* CommandToText(Command *cmd);
	Command* TextToCommand(const char* cmd_str);
};
