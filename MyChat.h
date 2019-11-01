#include "ClientP2P.h"
#include <vector>

struct ChatMessage{
	ChatMessage();
	ChatMessage(char *message);
	std::string msg_time;
	std::string name;
	std::string text;
	std::string ToString();
private:
	const static char separator = '^';
};

class MyChat {
private:
	P2PClient *client;
	ClientAddr *addr;
	clock_t last_clock;
	void Run();
public:
	MyChat();
	MyChat(ClientAddr* addr);
	void UpdateClientList();
	char* SendMessageToChat(char* chat_name, char* nickname, char* message);
	std::vector<ChatMessage>* GetChat(char* chat_name);
};

