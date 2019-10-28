#include "CommandInterpreter.h"

class StadnartCommandInterpreter: public ICommandInterpreter{
private:
	int sock;
	IDataWorker *dw;
public:
	void SetDataWorker(IDataWorker *dw);

	char* DoCommand(Command *cmd);
};

