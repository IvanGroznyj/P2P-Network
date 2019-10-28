#include "MainInterfaces.h"
#include "StandartCommandInterpreter.h"
#include <cstring>

	void StadnartCommandInterpreter::SetDataWorker(IDataWorker *dw){
		StadnartCommandInterpreter::dw = dw;
	}

	char* StadnartCommandInterpreter::DoCommand(Command *cmd){
		switch(cmd->name){
		case CmdHi:{
			return "\\('')";
		}
		case CmdEcho:{
			char *b = new char[cmd->argv[0].size()+1];
			strcpy(b, cmd->argv[0].c_str());
			return b;
		}
		case CmdHash:{
			char *b  = new char[cmd->argv[0].size()+1];
			strcpy(b, cmd->argv[0].c_str());
			string tmp = to_string(StadnartCommandInterpreter::dw->GetHash(b));
			char *p = new char[tmp.size()+1];
			strcpy(p, tmp.c_str());
			return p;
		}
		case CmdGetFile:{
			return StadnartCommandInterpreter::dw->GetFile((char*)cmd->argv[0].c_str());
		}

		case CmdGetVirtualFile:{
			cmd->argv[0] = "virtualdata/" + cmd->argv[0];
			return StadnartCommandInterpreter::dw->GetFileByName((char*)cmd->argv[0].c_str());
		}
		case CmdWriteToVirtualFile:{
			cmd->argv[0] = "virtualdata/" + cmd->argv[0];
			StadnartCommandInterpreter::dw->AppendToFileByName((char*)cmd->argv[0].c_str(), (char*)cmd->argv[1].c_str());
			return "OK";
		}
		default:
			return "Wrong cmd";
		}
	}

