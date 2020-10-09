/*
 *  Author: Ivan Khodyrev
 */
#include "MainInterfaces.h"
#include "StandartCommandInterpreter.h"
#include <cstring>
#include <vector>

using namespace std;
using namespace P2P_Network;

void Stadnart_Command_Interpreter::set_Data_Worker(I_Data_Worker *data_worker){
	Stadnart_Command_Interpreter::data_worker = data_worker;
}

extern vector<Client_Addr*>* get_Clients_From_Str(string str);

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
		Stadnart_Command_Interpreter::data_worker->write_To_File_By_Name(cmd->argv[0], cmd->argv[1], Rewrite_Mode);
		return "OK";
	}
	case Cmd_Append_To_Virtual_File:{
		cmd->argv[0] = Stadnart_Command_Interpreter::virtual_dir + cmd->argv[0];
		Stadnart_Command_Interpreter::data_worker->write_To_File_By_Name(cmd->argv[0], cmd->argv[1], Append_Mode);
		return "OK";
	}
	case Cmd_Add_Me:{
		string ips_file = Stadnart_Command_Interpreter::virtual_dir + "ips";
		Client_Addr addr(cmd->argv[0]);
		vector<Client_Addr*>* addrs = get_Clients_From_Str(Stadnart_Command_Interpreter::data_worker->get_File_By_Name(ips_file));
		bool in_addrs = false;
		for(int i=0; i<addrs->size(); i++){
			if(*(addrs->at(i)) == addr){
				in_addrs = true;
				break;
			}
		}
		if (!in_addrs) {
			Stadnart_Command_Interpreter::data_worker->write_To_File_By_Name(ips_file, cmd->argv[0], Append_Mode);
		}
		addrs->clear();
		return "OK";
	}
	default:
		return cmd->to_str();
	}
}
