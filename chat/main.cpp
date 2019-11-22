/*
 *  Author: Ivan Khodyrev
 */
#include <iostream>
#include "../MainInterfaces.h"
#include "../MyChat.h"
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[]){
	MyChat *chat = new MyChat(new ClientAddr(argv[1], atoi(argv[2])));
	sleep(1);
	char* nick = new char[256];
	char* buf = new char[256];
	string msg = "";
	cout<<"Enter login: ";
	cin.getline(nick, 256);
	while(1){
		chat->UpdateClientList();
		chat->UpdateChat("firstchat");
		cout<<"> ";
		cin.getline(buf, 256);
		msg = buf;
		
		if(msg.size()>0 && msg!="."){
			if(msg==".q"){
				break;
			}else{
				msg += '\n';
				char* res = chat->SendMessageToChat("firstchat", nick, (char*)msg.c_str());
			}
		}

		map<pair<string, string>, string> *msgs = chat->GetChat("firstchat");
		for(map<pair<string, string>, string>::iterator iter = msgs->begin(); iter != msgs->end(); iter++){
			cout<<iter->first.second<<": "<<iter->second;
		}
		
	}
	chat->Close();
	return 0;
}
