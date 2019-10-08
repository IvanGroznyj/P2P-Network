class P2PClient {
private:
	ISocketWorker *sworker;
	IRequestsHandler *handler;
	IDataWorker *dworker;
	char *ip;
	int port;
public:
	P2PClient();
	void BindClient(char* ip, int port);
	void StartListen();
	void StopListen();
	//void Build(StandartBuilder *builder);
	char* GetAnswer(char *ip, int port, char* msg, int msgsize);

	void SetSocketWorker(ISocketWorker* sw);
	void SetDataWorker(IDataWorker* dw);
	void SetRequestsHandler(IRequestsHandler* rh);
};
