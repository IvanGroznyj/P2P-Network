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

string Stadnart_Command_Interpreter::do_Command(Command *cmd){
	switch(cmd->name){
	case Cmd_Hi:{
		return "\\('')";
	}
	case Cmd_Echo:{
		return cmd->argv[0];
	}
	case Cmd_Hash:{
		return to_string(Stadnart_Command_Interpreter::data_worker->get_Hash(cmd->argv[0]));
	}
	case Cmd_Get_File:{
		return Stadnart_Command_Interpreter::data_worker->get_File(cmd->argv[0]);
	}
	case Cmd_Get_Virtual_File:{
		cmd->argv[0] = Stadnart_Command_Interpreter::virtual_dir + cmd->argv[0];
		return Stadnart_Command_Interpreter::data_worker->get_File_By_Name(cmd->argv[0]);
	}
	case Cmd_Write_To_Virtual_File:{
		cmd->argv[0] = Stadnart_Command_Interpreter::virtual_dir + cmd->argv[0];
		Stadnart_Command_Interpreter::data_worker->write_To_File_By_Name(cmd->argv[0], cmd->argv[1], Append_Mode);
		return "OK";
	}
	default:
		return cmd->to_str();
	}
}

