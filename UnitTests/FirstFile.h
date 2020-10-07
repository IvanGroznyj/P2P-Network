/*
 *  Author: Ivan Khodyrev
 */
#include "MainInterfaces.h"

#include "Client.h"
#include "CommandInterpreter.h"
#include "StandartObjectsFactory.h"
#include "NetSocketWorker.h"

#include "NatPMP.h"

#include <cstring>
#include <iostream>
#include <unistd.h>

#include <cxxtest/TestSuite.h>

using namespace std;
using namespace P2P_Network;

Client *c;
Core_Objects_Factory *factory;
// MyChat *chat;
Client_Addr* main_addr = new Client_Addr("127.0.0.1", 9094);

class MyTest: public CxxTest::TestSuite{
public:
	void testClient_Addr(){
		Client_Addr addr1("127.0.0.1", 9091);
		Client_Addr addr2("127.0.0.1", 9091);
		TS_ASSERT_EQUALS(addr1, addr2);

		Client_Addr addr3("127.0.0.1", 9093);
		TS_ASSERT_EQUALS(addr1 == addr3, false);

		Client_Addr addr4("127.0.0.2", 9091);
		TS_ASSERT_EQUALS(addr1 == addr4, false);
	}

	void testClient_AddrTranform(){
		char* addr = "127.0.0.1:9091";
		Client_Addr addr1(addr);
		TS_ASSERT_EQUALS(addr1.to_str(), addr);
	}

	void testTranslator(){
		Translator tr;
		char *txtcmd = "a|hello";
		Command *cmd = tr.text_To_Command(txtcmd);
		TS_ASSERT_EQUALS(tr.command_To_Text(cmd), txtcmd);
	}

	void testCommandsTypes(){
		Translator tr;
		Command *cmd = new Echo_Command("hello");
		Command *cmd2 = new Command(Cmd_Echo, "hello");
		TS_ASSERT_EQUALS(tr.command_To_Text(cmd), tr.command_To_Text(cmd2));
		cmd = new Hi_Command();
		cmd2 = new Command(Cmd_Hi);
		TS_ASSERT_EQUALS(tr.command_To_Text(cmd), tr.command_To_Text(cmd2));
		cmd = new Get_File_Command("123");
		cmd2 = new Command(Cmd_Get_File, "123");
		TS_ASSERT_EQUALS(tr.command_To_Text(cmd), tr.command_To_Text(cmd2));
	}

	void testCommandHi()
	{
		factory = new Standart_Objects_Factory();
		c = factory->get_Client();
		c->bind(main_addr);
		c->start_Listen();
		sleep(1);
		Translator tr;
		Command *cmd = new Hi_Command();
		
		const char *txtcmd = tr.command_To_Text(cmd);
		int len = strlen(txtcmd);
	    TS_ASSERT_EQUALS(c->get_Answer(main_addr, txtcmd, len), "\\('')");
	}

	void testCommandEcho()
	{
		Translator tr;
		Command *cmd = new Echo_Command("Hello");
		const char *txtcmd = tr.command_To_Text(cmd);
		int len = strlen(txtcmd);
	    TS_ASSERT_EQUALS( c->get_Answer(main_addr, txtcmd, len), "Hello");
	}

	void testCommandEchoShortAfterLong(){
		Translator tr;
		char *firststr = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
		char *secondstr = "helloworldmyfriends";
		Command *firstcmd = new Echo_Command(firststr);
		const char *txtcmd = tr.command_To_Text(firstcmd);
		int len = strlen(txtcmd);
		TS_ASSERT_EQUALS( c->get_Answer(main_addr, txtcmd, len), firststr);
		Command *secondcmd = new Echo_Command(secondstr);
		txtcmd = tr.command_To_Text(secondcmd);
		len = strlen(txtcmd);
		TS_ASSERT_EQUALS( c->get_Answer(main_addr, txtcmd, len), secondstr);
	}

	void testCommandHash(){
		Translator tr;
		Command *firstcmd = new Hash_Command("data/firstfile.txt");
		const char *txtcmd = tr.command_To_Text(firstcmd);
		int len = strlen(txtcmd);
		TS_ASSERT_EQUALS( c->get_Answer(main_addr, txtcmd, len), "2543331075"); // win: 2543331075 linux: 14761523821158082307
	}

	void testCommandGetFile(){
		Translator tr;
		Command *firstcmd = new Get_File_Command("2543331075"); // win: 2543331075 linux: 14761523821158082307
		const char *txtcmd = tr.command_To_Text(firstcmd);
		int len = strlen(txtcmd);
		// c->StopListen();
		TS_ASSERT_EQUALS( c->get_Answer(main_addr, txtcmd, len), "Hello\r\nIt's me!\r\nYou found me\r\n");
	}

	// void testChatMessage(){
	// 	char *message = "00:00^Ivan^hello\n";
	// 	ChatMessage msg(message);
	// 	TS_ASSERT_EQUALS(msg.ToString().c_str(), message);
	// }

	// void testChatSendMessage(){
	// 	chat = new MyChat(new Client_Addr("127.0.0.1", 9091));
	// 	chat->UpdateClientList();
	// 	char* res = chat->SendMessageToChat("firstchat", "mynick", "hello\n");
	// 	TS_ASSERT_EQUALS(res, "OK");
	// }

	// void testGetChat(){
	// 	chat->UpdateChat("firstchat");
	// 	map<pair<string, string>, string> *msgs = chat->GetChat("firstchat");
	// 	chat->Close();
	// 	TS_ASSERT_EQUALS((*msgs)[make_pair("2019-10-28_20:08:00","IG")], "hi\r\n");
	// }

	void testNATPMP(){
		Nat_PMP::port_Forwarding(Nat_PMP::TCP_CODE, 9095, 9095, 3600);
	}
};
