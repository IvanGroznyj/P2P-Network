#include "MainInterfaces.h"
#include "StandartCommandInterpreter.h"
#include "StandartDataWorker.h"
#include "NetSocketWorker.h"
#include "MyChat.h"
#include "StandartBuilder.h"
#include <cstring>
#include <algorithm>
#include <ctime>

ChatMessage::ChatMessage(){
	ChatMessage::msg_time = "";
	ChatMessage::name = "";
	ChatMessage::text = "";
}

ChatMessage::ChatMessage(char *message){
	ChatMessage::msg_time = "";
	ChatMessage::name = "";
	ChatMessage::text = "";
	char *iterator_ptr = message;
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

std::string ChatMessage::ToString(){
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
}

void MyChat::UpdateClientList(){
	MyChat::client->UpdateNodeAddrsInNetwork();
}

char* MyChat::SendMessageToChat(char* chat_name, char* nickname, char* message){
	Translator cmd_translator;
	ChatMessage msg;

	MyChat::client->UpdateGlobalTime();

	msg.msg_time = MyChat::client->GetNetworkTime();
	msg.name = nickname;
	msg.text = message;

	char *cmd_str = cmd_translator.CommandToText(new WriteToVirtualFileCommand(chat_name, (char*)msg.ToString().c_str()));
	std::vector<ClientAddr*> *addr_list = MyChat::client->GetNodeAddrsInNetwork();
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

std::vector<ChatMessage>* MyChat::GetChat(char* chat_name){
	Command *cmd = new GetVirtualFileCommand(chat_name);
	ICommandInterpreter* cmd_interpreter = new StadnartCommandInterpreter();
	cmd_interpreter->SetDataWorker(new StandartDataWorker());
	char *msgsText = cmd_interpreter->DoCommand(cmd);
	std::vector<ChatMessage> *msg_list = new std::vector<ChatMessage>();

	char *iterator_ptr = msgsText;
	std::string sum_buffer = "";
	while(*iterator_ptr != '\0'){
		if(*iterator_ptr=='\n'){
			sum_buffer+='\n';
			msg_list->push_back(ChatMessage((char*)sum_buffer.c_str()));
			sum_buffer = "";
		}else{
			sum_buffer += *iterator_ptr;
		}
		iterator_ptr++;
	}
	sort(msg_list->begin(), msg_list->end(), CompareChatMessages);
	return msg_list;
}
