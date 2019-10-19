#include "ClientP2P.h"
#include <vector>

struct ChatMessage{
	ChatMessage();
	ChatMessage(char *txtmessage);
	std::string time;
	std::string name;
	std::string text;
	std::string ToString();
};

class MyChat {
private:
	P2PClient *client;
	ClientAddr *addr;
	void Run();
public:
	MyChat();
	MyChat(ClientAddr* addr);
	void UpdateClientList();
	char* SendMessageToChat(char* chatName, char* message);
	std::vector<ChatMessage>* GetChat(ClientAddr *addr, char* chatName);
};

