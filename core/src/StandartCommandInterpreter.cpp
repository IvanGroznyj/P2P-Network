/*
 *  Author: Ivan Khodyrev
 */
#include "MainInterfaces.h"
#include "StandartCommandInterpreter.h"
#include <cstring>
using namespace std;

void StadnartCommandInterpreter::SetDataWorker(IDataWorker *data_worker){
	StadnartCommandInterpreter::data_worker = data_worker;
}

char* StadnartCommandInterpreter::DoCommand(Command *cmd){
	switch(cmd->name){
	case CmdHi:{
		return "\\('')";
	}
	case CmdEcho:{
		char *buffer = new char[cmd->argv[0].size()+1];
		strcpy(buffer, cmd->argv[0].c_str());
		return buffer;
	}
	case CmdHash:{
		string file_hash = to_string(StadnartCommandInterpreter::data_worker->GetHash(cmd->argv[0].c_str()));
		char *result_buffer = new char[file_hash.size()+1];
		strcpy(result_buffer, file_hash.c_str());
		return result_buffer;
	}
	case CmdGetFile:{
		return StadnartCommandInterpreter::data_worker->GetFile(cmd->argv[0].c_str());
	}
	case CmdGetVirtualFile:{
		cmd->argv[0] = StadnartCommandInterpreter::virtual_dir + cmd->argv[0];
		return StadnartCommandInterpreter::data_worker->GetFileByName(cmd->argv[0].c_str());
	}
	case CmdWriteToVirtualFile:{
		cmd->argv[0] = StadnartCommandInterpreter::virtual_dir + cmd->argv[0];
		StadnartCommandInterpreter::data_worker->AppendToFileByName(cmd->argv[0].c_str(), cmd->argv[1].c_str());
		return "OK";
	}
	case CmdGetAddresses:{

		return "";
	}
	default:
		return "Wrong cmd";
	}
}

