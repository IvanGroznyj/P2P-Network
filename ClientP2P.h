/*
 *  Author: Ivan Khodyrev
 */
#include <vector>
class P2PClient {
private:
	ISocketWorker *sworker;
	IRequestsHandler *handler;
	IDataWorker *dworker;
	ClientAddr* addr;
	char *net_time;
	std::vector<ClientAddr*> *addrs;
public:
	P2PClient();
	void BindClient(ClientAddr* addr);
	void StartListen();
	void StopListen();
	char* GetAnswer(ClientAddr* addr, const char* msg, int msg_size);
	void SetSocketWorker(ISocketWorker* sw);
	void SetDataWorker(IDataWorker* dw);
	void SetRequestsHandler(IRequestsHandler* rh);
	const char* GetNetworkTime();
	void UpdateGlobalTime();
	void UpdateNodeAddrsInNetwork();
	std::vector<ClientAddr*>* GetNodeAddrsInNetwork();
};
