#include "CommandInterpreter.h"

class StadnartCommandInterpreter: public ICommandInterpreter{
private:
	int sock;
	ISocketWorker *sw;
	IDataWorker *dw;
public:
	void SetCommandInterpreter(ISocketWorker *sw, IDataWorker *dw);

	void DoCommand(int sock, Command *cmd);
};

