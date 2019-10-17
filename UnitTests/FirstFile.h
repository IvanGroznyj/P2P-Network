#include "../MainInterfaces.h"
#include "../ClientP2P.h"

#include "../CommandInterpreter.h"
#include "../StandartBuilder.h"

#include <cstring>
#include <iostream>
#include <unistd.h>

#include <cxxtest/TestSuite.h>

P2PClient *c;
StandartBuilder *builder;
char *ip = (char*)"localhost";
int port = 9091;

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

		c->BindClient(ip,port);
		c->StartListen();
		sleep(1);

		Translator tr;
		Command *cmd = new HiCommand();
		char *txtcmd = tr.CommandToText(cmd);
		int len = strlen(txtcmd);
	    TS_ASSERT_EQUALS( c->GetAnswer(ip,port, txtcmd, len), "\\('')");
	 }
	void testCommandEcho()
	{
		Translator tr;
		Command *cmd = new EchoCommand("Hello");
		char *txtcmd = tr.CommandToText(cmd);
		int len = strlen(txtcmd);
	    TS_ASSERT_EQUALS( c->GetAnswer(ip,port, txtcmd, len), "Hello");
	}

	void testCommandEchoShortAfterLong(){
		Translator tr;
		char *firststr = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
		char *secondstr = "helloworldmyfriends";
		Command *firstcmd = new EchoCommand(firststr);
		char *txtcmd = tr.CommandToText(firstcmd);
		int len = strlen(txtcmd);
		TS_ASSERT_EQUALS( c->GetAnswer(ip,port, txtcmd, len), firststr);
		Command *secondcmd = new EchoCommand(secondstr);
		txtcmd = tr.CommandToText(secondcmd);
		len = strlen(txtcmd);
		TS_ASSERT_EQUALS( c->GetAnswer(ip,port, txtcmd, len), secondstr);
	}

	void testCommandHash(){
		Translator tr;
		Command *firstcmd = new HashCommand("data/firstfile.txt");
		char *txtcmd = tr.CommandToText(firstcmd);
		int len = strlen(txtcmd);
		TS_ASSERT_EQUALS( c->GetAnswer(ip,port, txtcmd, len), "2309636224852936099");
	}

	void testCommandGetFile(){
		Translator tr;
		Command *firstcmd = new GetFileCommand("2309636224852936099");
		char *txtcmd = tr.CommandToText(firstcmd);
		int len = strlen(txtcmd);
		TS_ASSERT_EQUALS( c->GetAnswer(ip,port, txtcmd, len), "Hello\nIt's me!\nYou found me");
	}
};