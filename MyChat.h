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
	CientAddress *addresses;
	char* ip;
	int port;
	void Run();
public:
	MyChat();
	MyChat(char *ip, int port);
	void UpdateClientList();
	char* SendMessageToChat(char* chatName, char* message);
	std::vector<ChatMessage>* GetChat(CientAddress *addr, char* chatName);
};

