/*
 *  Author: Ivan Khodyrev
 */
#include "MainInterfaces.h"
#include "StandartCommandInterpreter.h"
#include <cstring>

using namespace std;
using namespace P2P_Network;

void Stadnart_Command_Interpreter::set_Data_Worker(I_Data_Worker *data_worker){
	Stadnart_Command_Interpreter::data_worker = data_worker;
}

char* Stadnart_Command_Interpreter::do_Command(Command *cmd){
	switch(cmd->name){
	case Cmd_Hi:{
		return "\\('')";
	}
	case Cmd_Echo:{
		char *buffer = new char[cmd->argv[0].size()+1];
		strcpy(buffer, cmd->argv[0].c_str());
		return buffer;
	}
	case Cmd_Hash:{
		string file_hash = to_string(Stadnart_Command_Interpreter::data_worker->get_Hash(cmd->argv[0].c_str()));
		char *result_buffer = new char[file_hash.size()+1];
		strcpy(result_buffer, file_hash.c_str());
		return result_buffer;
	}
	case Cmd_Get_File:{
		return Stadnart_Command_Interpreter::data_worker->get_File(cmd->argv[0].c_str());
	}
	case Cmd_Get_Virtual_File:{
		cmd->argv[0] = Stadnart_Command_Interpreter::virtual_dir + cmd->argv[0];
		return Stadnart_Command_Interpreter::data_worker->get_File_By_Name(cmd->argv[0].c_str());
	}
	case Cmd_Write_To_Virtual_File:{
		cmd->argv[0] = Stadnart_Command_Interpreter::virtual_dir + cmd->argv[0];
		Stadnart_Command_Interpreter::data_worker->append_To_File_By_Name(cmd->argv[0].c_str(), cmd->argv[1].c_str());
		return "OK";
	}
	default:
		return "Wrong cmd";
	}
}

