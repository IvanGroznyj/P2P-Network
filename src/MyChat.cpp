/*
 *  Author: Ivan Khodyrev
 */
#include "../includes/MainInterfaces.h"
#include "../includes/StandartCommandInterpreter.h"
#include "../includes/StandartDataWorker.h"
#include "../includes/MyChat.h"
#include "../includes/StandartBuilder.h"
#include <cstring>
#include <algorithm>
#include <ctime>
#include <iostream>
using namespace std;

ChatMessage::ChatMessage(){
	ChatMessage::msg_time = "";
	ChatMessage::name = "";
	ChatMessage::text = "";
}

ChatMessage::ChatMessage(const char *message){
	ChatMessage::msg_time = "";
	ChatMessage::name = "";
	ChatMessage::text = "";
	const char *iterator_ptr = message;
	while(*iterator_ptr != ChatMessage::separator && *iterator_ptr != '\0'){
		ChatMessage::msg_time += *iterator_ptr;
		iterator_ptr++;
	}
	iterator_ptr++;
	while(*iterator_ptr != ChatMessage::separator && *iterator_ptr != '\0'){
		ChatMessage::name += *iterator_ptr;
		iterator_ptr++;
	}
	iterator_ptr++;
	while(*iterator_ptr != ChatMessage::separator && *iterator_ptr != '\0'){
		ChatMessage::text += *iterator_ptr;
		iterator_ptr++;
	}
}

string ChatMessage::ToString(){
	return ChatMessage::msg_time + ChatMessage::separator + ChatMessage::name + ChatMessage::separator + ChatMessage::text;
}

bool CompareChatMessages(ChatMessage msg1, ChatMessage msg2){
  return msg1.msg_time < msg2.msg_time;
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

	delete builder;
}

void MyChat::UpdateClientList(){
	MyChat::client->UpdateNodeAddrsInNetwork();
}

void MyChat::UpdateChat(char* chat_name){
	Translator cmd_translator;
	const char *cmd_str = cmd_translator.CommandToText(new GetVirtualFileCommand(chat_name));

	vector<ClientAddr*> *addr_list = MyChat::client->GetNodeAddrsInNetwork();
	char *result_buffer = "OK";
	int i=0;
	map<pair<string, string>, string>* cur_chat= MyChat::GetChat(chat_name);
	map<pair<string, string>, string>* tmp_chat;
	map<pair<string, string>, string>* new_chat = new map<pair<string, string>, string>();
	while(i < addr_list->size()){
		result_buffer = MyChat::client->GetAnswer((*addr_list)[i], cmd_str, strlen(cmd_str));
		if (result_buffer[0] != 'c' && result_buffer[1] != 'o' && result_buffer != "File can't open"){
			i++;


			tmp_chat = MyChat::ParseChatFromString(result_buffer);
			for(map<pair<string, string>, string>::iterator iter = tmp_chat->begin(); iter != tmp_chat->end(); iter++){
				if(cur_chat->count(iter->first) == 0){
					(*new_chat)[iter->first] = iter->second;
				}
			}

		}else{
			addr_list->erase(addr_list->begin()+i);
		}
	}
	if(new_chat->size()>0){
		ICommandInterpreter* cmd_interpreter = new StadnartCommandInterpreter();
		cmd_interpreter->SetDataWorker(new StandartDataWorker());
		char *chat_str =  MyChat::ConvertChatToString(new_chat);
		char *msg_list_str = cmd_interpreter->DoCommand(new WriteToVirtualFileCommand(chat_name, chat_str));

		delete msg_list_str;
		delete chat_str;
		delete cmd_interpreter;
	}

	delete tmp_chat;
	delete new_chat;
}

char* MyChat::SendMessageToChat(char* chat_name, char* nickname, char* message){
	Translator cmd_translator;
	ChatMessage msg;

	MyChat::client->UpdateGlobalTime();

	msg.msg_time = MyChat::client->GetNetworkTime();
	msg.name = nickname;
	msg.text = message;

	Command *cmd = new WriteToVirtualFileCommand(chat_name, msg.ToString().c_str());
	const char *cmd_str = cmd_translator.CommandToText(cmd);
	delete cmd;

	vector<ClientAddr*> *addr_list = MyChat::client->GetNodeAddrsInNetwork();
	char *result_buffer = "OK";
	int i=0;
	while(i < addr_list->size()){
		result_buffer = MyChat::client->GetAnswer((*addr_list)[i], cmd_str, strlen(cmd_str));
		if (result_buffer[0] == 'O' && result_buffer[1] == 'K'){
			i++;
		}else{
			addr_list->erase(addr_list->begin()+i);
		}
	}
	if(addr_list->size() > 0){
		result_buffer = "OK";
	} else{
		result_buffer = "ERROR";
	}
	return result_buffer;
}

map<pair<string, string>, string>* MyChat::GetChat(char* chat_name){
	Command *cmd = new GetVirtualFileCommand(chat_name);
	ICommandInterpreter* cmd_interpreter = new StadnartCommandInterpreter();
	cmd_interpreter->SetDataWorker(new StandartDataWorker());
	char *msg_list_str = cmd_interpreter->DoCommand(cmd);
	map<pair<string, string>, string> *msg_list = ParseChatFromString(msg_list_str);

	delete cmd;
	delete cmd_interpreter;
	return msg_list;
}

map<pair<string, string>, string>* MyChat::ParseChatFromString(char *chat_str){
	map<pair<string, string>, string> *msg_list = new map<pair<string, string>, string>();
	ChatMessage* tmp_msg;
	char *iterator_ptr = chat_str;
	string sum_buffer = "";
	while(*iterator_ptr != '\0'){
		if(*iterator_ptr=='\n'){
			sum_buffer+='\n';
			tmp_msg = new ChatMessage(sum_buffer.c_str());
			(*msg_list)[make_pair(tmp_msg->msg_time, tmp_msg->name)] = tmp_msg->text;
			delete tmp_msg;
			sum_buffer = "";
		}else{
			sum_buffer += *iterator_ptr;
		}
		iterator_ptr++;
	}
	return msg_list;
}

char* MyChat::ConvertChatToString(map<pair<string, string>, string>* chat){
	string sum_buffer = "";
	ChatMessage *tmp_msg;
	for(map<pair<string, string>, string>::iterator iter = chat->begin(); iter != chat->end(); iter++){
		tmp_msg = new ChatMessage();
		tmp_msg->msg_time = iter->first.first;
		tmp_msg->name = iter->first.second;
		tmp_msg->text = iter->second;
		sum_buffer += tmp_msg->ToString();
		delete tmp_msg;
	}
	char *result_buffer = new char[sum_buffer.size()+1];
	strcpy(result_buffer, sum_buffer.c_str());
	return result_buffer;
}

void MyChat::Close(){
	MyChat::client->StopListen();
}
