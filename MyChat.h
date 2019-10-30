#include "ClientP2P.h"
#include <vector>

struct ChatMessage{
	ChatMessage();
	ChatMessage(char *txtmessage);
	std::string msgtime;
	std::string name;
	std::string text;
	std::string ToString();
};

class MyChat {
private:
	P2PClient *client;
	ClientAddr *addr;
	clock_t lastClock;
	void Run();
public:
	MyChat();
	MyChat(ClientAddr* addr);
	void UpdateClientList();
	char* SendMessageToChat(char* chatName, char* nickname, char* message);
	std::vector<ChatMessage>* GetChat(char* chatName);
};

