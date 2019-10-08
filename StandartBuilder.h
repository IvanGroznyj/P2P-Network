class StandartBuilder {
private:
	ICommandInterpreter* cmdinter;
	IDataWorker* dw;
	ISocketWorker* sw;
	IRequestsHandler* rh;
public:
	void BuildSocketWorker();
	void BuildRequestsHandler();
	void BuildDataWorker();
	P2PClient* GetClient();
};
