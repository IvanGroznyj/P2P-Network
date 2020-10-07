/*
 *  Author: Ivan Khodyrev
 */
#include "Translator.h"
#include <cstring>
#include <sstream>

using namespace std;
using namespace P2P_Network;

const char* Translator::command_To_Text(Command* cmd){
	stringstream sum_str;
	sum_str << "";
	sum_str << cmd->name;
	for(int i=0; i < cmd->argc; i++){
		sum_str << '|' << (cmd->argv)[i];
	}
	char *result_buffer = new char[sum_str.str().size()+1];
	strcpy(result_buffer, sum_str.str().c_str());
	return result_buffer;
}

Command* Translator::text_To_Command(const char* cmd_str){
	Command *result_cmd = new Command();
	const char *passing_ptr = cmd_str;
	result_cmd->name = cmd_str[0];
	result_cmd->argc = 0;
	while(*passing_ptr!='\0'){
		if(*passing_ptr==Translator::separator) (result_cmd->argc)++;
		passing_ptr++;
	}
	passing_ptr=&cmd_str[0];
	passing_ptr++;
	result_cmd->argv = new string[result_cmd->argc];
	for(int i=0; i < (result_cmd->argc); i++){
		passing_ptr++;
		(result_cmd->argv)[i] = "";
		while(*passing_ptr!=Translator::separator && *passing_ptr!='\0'){
			(result_cmd->argv)[i] += *passing_ptr;
			passing_ptr++;
		}
	}
	return result_cmd;
}