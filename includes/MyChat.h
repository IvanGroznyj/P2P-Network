/*
 *  Author: Ivan Khodyrev
 */
#include "ClientP2P.h"
#include <vector>
#include <map>

using namespace std;

struct ChatMessage{
	ChatMessage();
	ChatMessage(const char *message);
	string msg_time;
	string name;
	string text;
	string ToString();
private:
	const static char separator = '^';
};

class MyChat {
private:
	P2PClient *client;
	ClientAddr *addr;
	// clock_t last_clock;
	void Run();
	map<pair<string, string>, string>* ParseChatFromString(char *chat_str);
	char* ConvertChatToString(map<pair<string, string>, string>* chat);
public:
	MyChat();
	MyChat(ClientAddr* addr);
	void UpdateClientList();
	void UpdateChat(char* chat_name);
	char* SendMessageToChat(char* chat_name, char* nickname, char* message);
	map<pair<string, string>, string>* GetChat(char* chat_name);
	void Close();
};

