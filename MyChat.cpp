#include "MainInterfaces.h"
#include "CommandInterpreter.h"
#include "MyChat.h"
#include "StandartBuilder.h"
#include <cstring>
#include <algorithm>

ChatMessage::ChatMessage(){
	ChatMessage::time = "";
	ChatMessage::name = "";
	ChatMessage::text = "";
}

ChatMessage::ChatMessage(char *txtmessage){
	ChatMessage::time = "";
	ChatMessage::name = "";
	ChatMessage::text = "";
	char *p = txtmessage;
	while(*p != '^' && *p != '\0'){
		ChatMessage::time += *p;
		p++;
	}
	p++;
	while(*p != '^' && *p != '\0'){
		ChatMessage::name += *p;
		p++;
	}
	p++;
	while(*p != '^' && *p != '\0'){
		ChatMessage::text += *p;
		p++;
	}
}

std::string ChatMessage::ToString(){
	return ChatMessage::time + '^' + ChatMessage::name + '^' + ChatMessage::text;
}

bool CompareChatMessages(ChatMessage msg1, ChatMessage msg2){
  return msg1.time < msg2.time;
}


MyChat::MyChat() {
	MyChat::addr = new ClientAddr("localhost", 9091);
	MyChat::Run();
}

MyChat::MyChat(ClientAddr *addr){
	MyChat::addr = addr;
	MyChat::Run();
}

void MyChat::Run(){
	StandartBuilder *builder = new StandartBuilder();
		builder->BuildDataWorker();
		builder->BuildSocketWorker();
		builder->BuildRequestsHandler();
		MyChat::client = builder->GetClient();
		MyChat::client->BindClient(MyChat::addr);
		MyChat::client->StartListen();
}

void MyChat::UpdateClientList(){

}

char* MyChat::SendMessageToChat(char* chatName, char* message){
	Translator tr;
	ChatMessage msg;
	msg.time = MyChat::client->GetNetworkTime();
	msg.name = "Ivan";
	msg.text = message;
	char *txtcmd = tr.CommandToText(new WriteToVirtualFileCommand(chatName, (char*)msg.ToString().c_str()));
	std::vector<ClientAddr*> *addrs = MyChat::client->GetNodeAddrsInNetwork();
	char *res = "OK";
	for(int i=0; i<addrs->size(); i++)
		res = MyChat::client->GetAnswer((*addrs)[i], txtcmd, strlen(txtcmd));
	return res;
}

std::vector<ChatMessage>* MyChat::GetChat(ClientAddr *addr, char* chatName){
	Translator tr;
	char *txtcmd = tr.CommandToText(new GetVirtualFileCommand(chatName));
	char *msgsText = MyChat::client->GetAnswer(addr, txtcmd, strlen(txtcmd));
	std::vector<ChatMessage> *msgs = new std::vector<ChatMessage>();

	char *p = msgsText;
	std::string tmp = "";
	while(*p != '\0'){
		if(*p=='\n'){
			tmp+='\n';
			msgs->push_back(ChatMessage((char*)tmp.c_str()));
			tmp = "";
		}else{
			tmp += *p;
		}
		p++;
	}
	sort(msgs->begin(), msgs->end(), CompareChatMessages);
	return msgs;
}
