#include <thread>

class ThreadRequestsHandler: public IRequestsHandler{
private:
	ISocketWorker *sw;
	IDataWorker *dw;
	std::thread *mainThreadHandler;
	bool isWorking = false;
public:
	void SetWorkers(ISocketWorker *sworker, ICommandInterpreter *cmdinterpreter);

	void StartWorking(ClientAddr* addr);

	int GetStatus();

	void StopWorking();
};
