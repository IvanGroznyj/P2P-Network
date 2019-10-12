#include "MainInterfaces.h"
#include "StandartCommandInterpreter.h"
#include <cstring>

	void StadnartCommandInterpreter::SetCommandInterpreter(ISocketWorker *sw, IDataWorker *dw){
		StadnartCommandInterpreter::sw = sw;
		StadnartCommandInterpreter::dw = dw;
	}

	void StadnartCommandInterpreter::DoCommand(int sock, Command *cmd){
		switch(cmd->name){
		case CmdHi:{
			StadnartCommandInterpreter::sw->Send(sock, (char*)"\\('')", 7);
			break;
		}
		case CmdEcho:{
			char *b = new char[cmd->argv[0].size()+1];
			strcpy(b, cmd->argv[0].c_str());
			StadnartCommandInterpreter::sw->Send(sock, b, cmd->argv[0].size()+1);
			break;
		}
		case CmdHash:{
			char *b  = new char[cmd->argv[0].size()+1];
			strcpy(b, cmd->argv[0].c_str());
			string tmp = to_string(StadnartCommandInterpreter::dw->GetHash(b));
			char p[tmp.size()+1];
			strcpy(p, tmp.c_str());
			StadnartCommandInterpreter::sw->Send(sock, p, sizeof(p));
			break;
		}
		case CmdGetFile:{
			char *file = StadnartCommandInterpreter::dw->GetFile((char*)cmd->argv[0].c_str());
			int len = strlen(file);
			StadnartCommandInterpreter::sw->Send(sock, file, len+1);
			break;
		}
		default:
			StadnartCommandInterpreter::sw->Send(sock,(char*)"Wrong cmd", 10);
		}

		/*if(cmd->name == "echo"){
			char *b = new char[cmd->argv[0].size()+1];
			strcpy(b, cmd->argv[0].c_str());
			StadnartCommandInterpreter::sw->Send(sock, b, cmd->argv[0].size()+1);
		}else

		if(cmd->name == "hi"){

		}else

		if(cmd->name == "hash"){
			char *b  = new char[cmd->argv[0].size()];
			strcpy(b, cmd->argv[0].c_str());
			string tmp = to_string(StadnartCommandInterpreter::dw->GetHash(b));
			char p[tmp.size()+1];
			strcpy(p, tmp.c_str());
			StadnartCommandInterpreter::sw->Send(sock, p, sizeof(p));
		}else
			StadnartCommandInterpreter::sw->Send(sock,(char*)"Wrong cmd", 10);
			*/

	}

