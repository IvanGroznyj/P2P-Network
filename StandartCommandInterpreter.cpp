#include "MainInterfaces.h"
#include "StandartCommandInterpreter.h"

	void StadnartCommandInterpreter::SetCommandInterpreter(ISocketWorker *sw, IDataWorker *dw){
		StadnartCommandInterpreter::sw = sw;
		StadnartCommandInterpreter::dw = dw;
	}

	void StadnartCommandInterpreter::DoCommand(int sock, Command *cmd){
		if(cmd->name == "echo"){
			char *b = new char[cmd->argv[0].size()+1];
			strcpy(b, cmd->argv[0].c_str());
			StadnartCommandInterpreter::sw->Send(sock, b, cmd->argv[0].size()+1);
		}else

		if(cmd->name == "hi"){
			StadnartCommandInterpreter::sw->Send(sock, (char*)"\\('')\n", 7);
		}else

		if(cmd->name == "hash"){
			char *b  = new char[cmd->argv[0].size()];
			strcpy(b, cmd->argv[0].c_str());
			string tmp = to_string(StadnartCommandInterpreter::dw->GetHash(b));
			char p[tmp.size()+1];
			strcpy(p, tmp.c_str());
			StadnartCommandInterpreter::sw->Send(sock, p, sizeof(p));
		}else
			StadnartCommandInterpreter::sw->Send(sock,(char*)"Wrong cmd", 9);

	}

