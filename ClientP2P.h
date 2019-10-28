#include <vector>
class P2PClient {
private:
	ISocketWorker *sworker;
	IRequestsHandler *handler;
	IDataWorker *dworker;
	ClientAddr* addr;
	char *netTime;
	std::vector<ClientAddr*> *addrs;
public:
	P2PClient();
	void BindClient(ClientAddr* addr);
	void StartListen();
	void StopListen();
	char* GetAnswer(ClientAddr* addr, char* msg, int msgsize);
	void SetSocketWorker(ISocketWorker* sw);
	void SetDataWorker(IDataWorker* dw);
	void SetRequestsHandler(IRequestsHandler* rh);
	char* GetNetworkTime();
	void UpdateGlobalTime();
	void UpdateNodeAddrsInNetwork();
	std::vector<ClientAddr*>* GetNodeAddrsInNetwork();
};
