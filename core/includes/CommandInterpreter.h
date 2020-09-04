/*
 *  Author: Ivan Khodyrev
 */

#ifndef CommandInterpreter_H
#define CommandInterpreter_H

#include "Translator.h"

class ICommandInterpreter {
public:
	virtual void SetDataWorker(IDataWorker *dw)=0;
	virtual char* DoCommand(Command *cmd)=0;
};

#endif