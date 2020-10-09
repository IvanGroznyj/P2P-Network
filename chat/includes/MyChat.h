/*
 *  Author: Ivan Khodyrev
 */

#ifndef MyChat_H
#define MyChat_H

#include "Client.h"
#include <vector>
#include <map>

using namespace P2P_Network;
using namespace std;

struct ChatMessage{
	ChatMessage();
	ChatMessage(string message);
	string msg_time;
	string name;
	string text;
	string ToString();
private:
	const string separator = "^";
};

class MyChat {
private:
	Client *client;
	Client_Addr *addr;
	// clock_t last_clock;
	void Run();
	map<pair<string, string>, string>* ParseChatFromString(string chat_str);
	string ConvertChatToString(map<pair<string, string>, string>* chat);
public:
	MyChat();
	MyChat(Client_Addr* addr);
	void UpdateClientList();
	void UpdateChat(string chat_name);
	string SendMessageToChat(string chat_name, string nickname, string message);
	map<pair<string, string>, string>* GetChat(string chat_name);
	void Close();
};

#endif