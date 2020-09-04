/*
 *  Author: Ivan Khodyrev
 */
#include "MainInterfaces.h"
#include "MyChat.h"

#include "CommandInterpreter.h"
#include "StandartBuilder.h"
#include "NetSocketWorker.h"

#include "NatPMP.h"

#include <cstring>
#include <iostream>
#include <unistd.h>

#include <cxxtest/TestSuite.h>

P2PClient *c;
StandartBuilder *builder;
MyChat *chat;
ClientAddr* main_addr = new ClientAddr("127.0.0.1", 9094);

class MyTest: public CxxTest::TestSuite{
public:
	void testClientAddr(){
		ClientAddr addr1("127.0.0.1", 9091);
		ClientAddr addr2("127.0.0.1", 9091);
		TS_ASSERT_EQUALS(addr1 == addr2, true);

		ClientAddr addr3("127.0.0.1", 9093);
		TS_ASSERT_EQUALS(addr1 == addr3, false);

		ClientAddr addr4("127.0.0.2", 9091);
		TS_ASSERT_EQUALS(addr1 == addr4, false);
	}

	void testTranslator(){
		Translator tr;
		char *txtcmd = "a|hello";
		Command *cmd = tr.TextToCommand(txtcmd);
		TS_ASSERT_EQUALS(tr.CommandToText(cmd), txtcmd);
	}

	void testCommandsTypes(){
		Translator tr;
		Command *cmd = new EchoCommand("hello");
		Command *cmd2 = new Command(CmdEcho, "hello");
		TS_ASSERT_EQUALS(tr.CommandToText(cmd), tr.CommandToText(cmd2));
		cmd = new HiCommand();
		cmd2 = new Command(CmdHi);
		TS_ASSERT_EQUALS(tr.CommandToText(cmd), tr.CommandToText(cmd2));
		cmd = new GetFileCommand("123");
		cmd2 = new Command(CmdGetFile, "123");
		TS_ASSERT_EQUALS(tr.CommandToText(cmd), tr.CommandToText(cmd2));
	}

	void testCommandHi()
	{
		builder = new StandartBuilder();
		builder->BuildDataWorker();
		builder->BuildSocketWorker();
		builder->BuildRequestsHandler();

		c = builder->GetClient();

		c->BindClient(main_addr);
		c->StartListen();
		sleep(1);
		Translator tr;
		Command *cmd = new HiCommand();
		
		const char *txtcmd = tr.CommandToText(cmd);
		int len = strlen(txtcmd);
	    TS_ASSERT_EQUALS(c->GetAnswer(main_addr, txtcmd, len), "\\('')");
	 }
	void testCommandEcho()
	{
		Translator tr;
		Command *cmd = new EchoCommand("Hello");
		const char *txtcmd = tr.CommandToText(cmd);
		int len = strlen(txtcmd);
	    TS_ASSERT_EQUALS( c->GetAnswer(main_addr, txtcmd, len), "Hello");
	}

	void testCommandEchoShortAfterLong(){
		Translator tr;
		char *firststr = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
		char *secondstr = "helloworldmyfriends";
		Command *firstcmd = new EchoCommand(firststr);
		const char *txtcmd = tr.CommandToText(firstcmd);
		int len = strlen(txtcmd);
		TS_ASSERT_EQUALS( c->GetAnswer(main_addr, txtcmd, len), firststr);
		Command *secondcmd = new EchoCommand(secondstr);
		txtcmd = tr.CommandToText(secondcmd);
		len = strlen(txtcmd);
		TS_ASSERT_EQUALS( c->GetAnswer(main_addr, txtcmd, len), secondstr);
	}

	void testCommandHash(){
		Translator tr;
		Command *firstcmd = new HashCommand("data/firstfile.txt");
		const char *txtcmd = tr.CommandToText(firstcmd);
		int len = strlen(txtcmd);
		TS_ASSERT_EQUALS( c->GetAnswer(main_addr, txtcmd, len), "2543331075"); // win: 2543331075 linux: 14761523821158082307
	}

	void testCommandGetFile(){
		Translator tr;
		Command *firstcmd = new GetFileCommand("2543331075"); // win: 2543331075 linux: 14761523821158082307
		const char *txtcmd = tr.CommandToText(firstcmd);
		int len = strlen(txtcmd);
		// c->StopListen();
		TS_ASSERT_EQUALS( c->GetAnswer(main_addr, txtcmd, len), "Hello\r\nIt's me!\r\nYou found me\r\n");
	}

	// void testChatMessage(){
	// 	char *message = "00:00^Ivan^hello\n";
	// 	ChatMessage msg(message);
	// 	TS_ASSERT_EQUALS(msg.ToString().c_str(), message);
	// }

	// void testChatSendMessage(){
	// 	chat = new MyChat(new ClientAddr("127.0.0.1", 9091));
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
		NatPMP::PortForwarding(NatPMP::TCP_CODE, 9095, 9095, 3600);
	}
};
