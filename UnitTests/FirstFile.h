#include "../MainInterfaces.h"
#include "../MyChat.h"

#include "../CommandInterpreter.h"
#include "../StandartBuilder.h"
#include "../NetSocketWorker.h"

#include <cstring>
#include <iostream>
#include <unistd.h>

#include <cxxtest/TestSuite.h>

P2PClient *c;
StandartBuilder *builder;
MyChat *chat;
ClientAddr* main_addr = new ClientAddr("localhost", 9091);

class MyTest: public CxxTest::TestSuite{
public:
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
		char *txtcmd = tr.CommandToText(cmd);
		int len = strlen(txtcmd);
	    TS_ASSERT_EQUALS( c->GetAnswer(main_addr, txtcmd, len), "\\('')");
	 }
	void testCommandEcho()
	{
		Translator tr;
		Command *cmd = new EchoCommand("Hello");
		char *txtcmd = tr.CommandToText(cmd);
		int len = strlen(txtcmd);
	    TS_ASSERT_EQUALS( c->GetAnswer(main_addr, txtcmd, len), "Hello");
	}

	void testCommandEchoShortAfterLong(){
		Translator tr;
		char *firststr = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
		char *secondstr = "helloworldmyfriends";
		Command *firstcmd = new EchoCommand(firststr);
		char *txtcmd = tr.CommandToText(firstcmd);
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
		char *txtcmd = tr.CommandToText(firstcmd);
		int len = strlen(txtcmd);
		TS_ASSERT_EQUALS( c->GetAnswer(main_addr, txtcmd, len), "2309636224852936099");
	}

	void testCommandGetFile(){
		Translator tr;
		Command *firstcmd = new GetFileCommand("2309636224852936099");
		char *txtcmd = tr.CommandToText(firstcmd);
		int len = strlen(txtcmd);
		TS_ASSERT_EQUALS( c->GetAnswer(main_addr, txtcmd, len), "Hello\nIt's me!\nYou found me");
	}

	void testChatMessage(){
		char *message = "00:00^Ivan^hello\n";
		ChatMessage msg(message);
		TS_ASSERT_EQUALS(msg.ToString().c_str(), message);
	}

	void testChatSendMessage(){
		c->StopListen();
		sleep(1);
		chat = new MyChat(new ClientAddr("localhost", 9092));
		sleep(1);
		chat->UpdateClientList();
		char* res = chat->SendMessageToChat("firstchat", "hello\n");
		TS_ASSERT_EQUALS(res, "OK");
	}

	void testGetChat(){
		ClientAddr *addr = new ClientAddr("localhost", 9092);
		std::vector<ChatMessage> *msgs = chat->GetChat(addr, "firstchat");
		TS_ASSERT_EQUALS(msgs->at(0).text, "hi\n");
	}

	void testHTTP(){
		ISocketWorker *sw = new NetSocketWorker();
		int sock = sw->GetNewSocketId();
		sw->Bind(sock, new ClientAddr("185.48.37.119",16433));
		ClientAddr *addr = new ClientAddr("igp2p.000webhostapp.com", 80);
		int res = sw->ConnectTo(sock, addr);
		TS_ASSERT(res>=0);
		char *req = "GET /?cmd=getAddrs HTTP/1.1\r\nHost: igp2p.000webhostapp.com\r\n\r\n";
		sw->Send(sock, req, strlen(req));
		printf("Sended\n");
		//sleep(5);
		char *buf = new char[1024];
		sw->Recieve(sock, buf, 1024);
		char *p = buf;
		int k = 0;
		while (*p!='\0'){
			if(k==11) cout<<*p;
			if(*p=='\n') k++;
			p++;
		}
		//while(1){}
	}
};
