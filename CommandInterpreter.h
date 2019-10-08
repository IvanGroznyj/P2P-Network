#include "Translator.h"

class ICommandInterpreter {
public:
	virtual void SetCommandInterpreter(ISocketWorker *sw, IDataWorker *dw)=0;
	virtual void DoCommand(int sock, Command *cmd)=0;
};
