#include "MainInterfaces.h"
#include "ClientP2P.h"

#include "CommandInterpreter.h"
#include "StandartBuilder.h"

#include <iostream>
#include <unistd.h>

using namespace std;

void P2PClientConnectionTest();
void HashSumTest();
void TranslatorTest();


P2PClient *c;
StandartBuilder *builder;
char *ip = (char*)"localhost";
int port = 9091;

int main(int argc, char* argv[]){
	StandartBuilder *builder = new StandartBuilder();
	builder->BuildDataWorker();
	builder->BuildSocketWorker();
	builder->BuildRequestsHandler();

	P2PClient *c = builder->GetClient();

	if(argc==3){
		ip = argv[1];
		port = atoi(argv[2]);
	}
	c->BindClient(ip,port);
	cout<<"start...\n";
	c->StartListen();


	string tmp;
	int portdest;
	cout<<"Enter ip: ";
	cin>>tmp;
	char *ipdest = new char[tmp.size()];
	strcpy(ipdest, tmp.c_str());
	cout<<"Enter port: ";
	cin>>portdest;
	Command *cmd = new Command();
	cmd->argv = new string[1];
	cmd->argc = 1;
	Translator tr;
	while(true){
		cout<<"Cmd: ";
		cin>>cmd->name;
		cout<<"text: ";
		cin>>cmd->argv[0];
		cout<<"Get cmd: "<<cmd->argv[0]<<"; Size: "<<cmd->argv[0].size()<<endl;
		cout<<"> "<<c->GetAnswer(ipdest, portdest, tr.CommandToText(cmd), cmd->argv[0].size()+cmd->name.size()+1)<<endl;
	}

	// !!! TESTS !!!
	sleep(2);
	P2PClientConnectionTest();
	//HashSumTest();
	//TranslatorTest();

	c->StopListen();

	//sleep(20);
	//while(true){}
	cout<<"stoped\n";
	return 0;
}

/* !!! TESTS !!!*/
  	void P2PClientConnectionTest(){
	char message[] = "/home/olaf/Documents/University/OS/sem2.cpp";
	Command *cmd = new Command();
	cmd->name = "hi";
	cmd->argc = 1;
	cmd->argv = new string[1];
	cmd->argv[0] = "/home/olaf/Documents/University/OS/sem2.cpp";
	Translator tr;
	cout<<"# LoopConnectionTest\n";
	cout<<"Cmd: "<<tr.CommandToText(cmd)<<endl;
	cout<<"Answer: "<< c->GetAnswer(ip, port, tr.CommandToText(cmd), sizeof(message)+(cmd->name).size())<<endl;
	cout<<"# end of test\n";
}
  /*
void HashSumTest(){
	cout<<"# HashSumTest\n";
	IDataWorker *dw = builder->BuildDataWorker();
	cout<<dw->GetHash("/home/olaf/Documents/University/OS/sem2.cpp")<<"\n";
	cout<<dw->GetHash("/home/olaf/Documents/University/OS/sem3.cpp")<<"\n";
	cout<<"# end of test\n";
}
void TranslatorTest(){
	cout<<"# TranslatorTest\n";
	Translator *tr = new Translator();
	Command *tmpcmd = new Command();
	tmpcmd->name = "hello";
	tmpcmd->argv = new string[2];
	tmpcmd->argc = 	2;
	tmpcmd->argv[0] = "arg1";
	tmpcmd->argv[1] = "arg2";
	char *res = tr->CommandToText(tmpcmd);
	cout<<"InText: "<<res<<endl;
	tmpcmd = tr->TextToCommand(res);
	cout<<"InCommand: name = "<<tmpcmd->name<<endl;
	cout<<"InCommand: argc = "<<tmpcmd->argc<<endl;
	for(int i=0; i<tmpcmd->argc; i++){
		cout<<"InCommand: argv["<<i<<"] = "<<(tmpcmd->argv)[i]<<endl;
	}
	cout<<"# end of test\n";
}*/
