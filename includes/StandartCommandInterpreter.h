/*
 *  Author: Ivan Khodyrev
 */
#include "CommandInterpreter.h"

class StadnartCommandInterpreter: public ICommandInterpreter{
private:
	int sock_id;
	IDataWorker *data_worker;
	const char* virtual_dir = "virtualdata/";
public:
	void SetDataWorker(IDataWorker *data_worker);

	char* DoCommand(Command *cmd);
};

