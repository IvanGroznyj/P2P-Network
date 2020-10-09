/*
 *  Author: Ivan Khodyrev
 */
#include "MainInterfaces.h"
#include "StandartCommandInterpreter.h"
#include "StandartDataWorker.h"
#include "MyChat.h"
#include "StandartObjectsFactory.h"
#include <cstring>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <sstream>

using namespace std;
Core_Objects_Factory *factory;

ChatMessage::ChatMessage(){
	ChatMessage::msg_time = "";
	ChatMessage::name = "";
	ChatMessage::text = "";
}

ChatMessage::ChatMessage(string message){
	int start_pos, end_pos;
	start_pos = 0;
	end_pos = message.find(ChatMessage::separator, start_pos);
	ChatMessage::msg_time = message.substr(start_pos, end_pos - start_pos);

	start_pos = end_pos + 1;
	end_pos = message.find(ChatMessage::separator, start_pos);
	ChatMessage::name =  message.substr(start_pos, end_pos - start_pos);

	start_pos = end_pos + 1;
	ChatMessage::text = message.substr(start_pos);
}

string ChatMessage::ToString(){
	return ChatMessage::msg_time + ChatMessage::separator + ChatMessage::name + ChatMessage::separator + ChatMessage::text;
}

bool CompareChatMessages(ChatMessage msg1, ChatMessage msg2){
  return msg1.msg_time < msg2.msg_time;
}


MyChat::MyChat() {
	MyChat::addr = new Client_Addr("localhost", 9091);
	MyChat::Run();
}

MyChat::MyChat(Client_Addr *addr){
	MyChat::addr = addr;
	MyChat::Run();
}

void MyChat::Run(){
	factory = new Standart_Objects_Factory();
	MyChat::client = factory->get_Client();
	MyChat::client->bind(MyChat::addr);
	MyChat::client->start_Listen();
}

void MyChat::UpdateClientList(){
	MyChat::client->update_Node_Addrs_In_Network();
}

void MyChat::UpdateChat(string chat_name){
	string cmd_str = Get_Virtual_File_Command(chat_name).to_str();

	vector<Client_Addr*> *addr_list = MyChat::client->get_Node_Addrs_In_Network();
	int i=0;
	map<pair<string, string>, string>* cur_chat = MyChat::GetChat(chat_name);
	map<pair<string, string>, string>* tmp_chat;
	map<pair<string, string>, string>* new_chat = new map<pair<string, string>, string>();
	while(i < addr_list->size()){
		Response_Body response = MyChat::client->get_Answer(addr_list->at(i), cmd_str);
		if (response == OK && response.response_text != "File can't open"){
			i++;
			tmp_chat = MyChat::ParseChatFromString(response.response_text);
			for(map<pair<string, string>, string>::iterator iter = tmp_chat->begin(); iter != tmp_chat->end(); iter++){
				if(cur_chat->count(iter->first) == 0){
					(*cur_chat)[iter->first] = iter->second;
					(*new_chat)[iter->first] = iter->second;
				}
			}
		}else{
			addr_list->erase(addr_list->begin()+i);
		}
	}
	if(new_chat->size()>0){
		I_Command_Interpreter* cmd_interpreter = factory->get_Command_Interpreter();
		string chat_str =  MyChat::ConvertChatToString(new_chat);
		string msg_list_str = cmd_interpreter->do_Command(new Write_To_Virtual_File_Command(chat_name, chat_str));

		delete cmd_interpreter;
	}

	delete tmp_chat;
	delete new_chat;
}

string MyChat::SendMessageToChat(string chat_name, string nickname, string message){
	ChatMessage msg;

	MyChat::client->update_Global_Time();

	msg.msg_time = MyChat::client->get_Network_Time();
	msg.name = nickname;
	msg.text = message;

	Command *cmd = new Write_To_Virtual_File_Command(chat_name, msg.ToString());
	string cmd_str = cmd->to_str();
	delete cmd;

	vector<Client_Addr*> *addr_list = MyChat::client->get_Node_Addrs_In_Network();
	string result_buffer = "OK";
	int i=0;
	while(i < addr_list->size()){
		Response_Body response = MyChat::client->get_Answer((*addr_list)[i], cmd_str);
		if (response == OK){
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

map<pair<string, string>, string>* MyChat::GetChat(string chat_name){
	Command *cmd = new Get_Virtual_File_Command(chat_name);
	I_Command_Interpreter* cmd_interpreter = factory->get_Command_Interpreter();
	string msg_list_str = cmd_interpreter->do_Command(cmd);
	map<pair<string, string>, string> *msg_list = ParseChatFromString(msg_list_str);

	delete cmd;
	delete cmd_interpreter;
	return msg_list;
}

map<pair<string, string>, string>* MyChat::ParseChatFromString(string chat_str){
	map<pair<string, string>, string> *msg_list = new map<pair<string, string>, string>();
	ChatMessage* tmp_msg;

	int start_pos, end_pos;

	start_pos = chat_str.find("\n");
	vector<string> args;
	if (start_pos != string::npos){
		start_pos = 0;
		end_pos = chat_str.find("\n", start_pos);
		while(end_pos != string::npos){
			tmp_msg = new ChatMessage(chat_str.substr(start_pos, end_pos - start_pos));
			(*msg_list)[make_pair(tmp_msg->msg_time, tmp_msg->name)] = tmp_msg->text;
			start_pos = end_pos + 1;
			end_pos = chat_str.find("\n", start_pos);		
		}
		// tmp_msg = new ChatMessage(chat_str.substr(start_pos));
		// (*msg_list)[make_pair(tmp_msg->msg_time, tmp_msg->name)] = tmp_msg->text;
	}
	return msg_list;
}

string MyChat::ConvertChatToString(map<pair<string, string>, string>* chat){
	stringstream sum_buffer;
	sum_buffer << "";
	ChatMessage *tmp_msg;
	for(map<pair<string, string>, string>::iterator iter = chat->begin(); iter != chat->end(); iter++){
		tmp_msg = new ChatMessage();
		tmp_msg->msg_time = iter->first.first;
		tmp_msg->name = iter->first.second;
		tmp_msg->text = iter->second;
		sum_buffer << tmp_msg->ToString() << "\n";
		delete tmp_msg;
	}
	return sum_buffer.str();
}

void MyChat::Close(){
	MyChat::client->stop_Listen();
}
