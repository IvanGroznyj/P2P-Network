/*
 *  Author: Ivan Khodyrev
 */
#include "Translator.h"

class ICommandInterpreter {
public:
	virtual void SetDataWorker(IDataWorker *dw)=0;
	virtual char* DoCommand(Command *cmd)=0;
};
