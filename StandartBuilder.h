class StandartBuilder {
private:
	ICommandInterpreter* cmd_interpeter;
	IDataWorker* data_worker;
	ISocketWorker* socket_worker;
	IRequestsHandler* request_handler;
public:
	void BuildSocketWorker();
	void BuildRequestsHandler();
	void BuildDataWorker();
	P2PClient* GetClient();
};
