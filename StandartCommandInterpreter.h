#include "CommandInterpreter.h"

class StadnartCommandInterpreter: public ICommandInterpreter{
private:
	int sock;
	ISocketWorker *sw;
	IDataWorker *dw;
public:
	void SetDataWorker(IDataWorker *dw);

	char* DoCommand(Command *cmd);
};

