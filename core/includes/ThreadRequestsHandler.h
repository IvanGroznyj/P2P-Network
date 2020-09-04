/*
 *  Author: Ivan Khodyrev
 */

#ifndef ThreadRequestsHandler_H
#define ThreadRequestsHandler_H

class ThreadRequestsHandler: public IRequestsHandler{
private:
	ISocketWorker *socket_worker;
	IDataWorker *data_worker;
	bool is_working = false;
public:
	void SetWorkers(ISocketWorker *socket_worker, ICommandInterpreter *cmd_interpeter);

	void StartWorking(ClientAddr* addr);

	int GetStatus();

	void StopWorking();
};

#endif