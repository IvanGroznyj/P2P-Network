/*
 *  Author: Ivan Khodyrev
 */

#ifndef Translator_H
#define Translator_H

#include "Commands.h"

class Translator {
private:
	const static char separator = '|';
public:
	const char* CommandToText(Command *cmd);
	Command* TextToCommand(const char* cmd_str);
};

#endif Translator_H