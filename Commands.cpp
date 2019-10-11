#include "Commands.h"


HiCommand::HiCommand(){}

Command* HiCommand::ToStandartCommand(){
	Command* cmd = new Command();
	cmd->name = "hi";
	cmd->argc = 0;
	cmd->argv = nullptr;
	return cmd;
}

EchoCommand::EchoCommand(char* text){
	EchoCommand::text = text;
}

Command* EchoCommand::ToStandartCommand(){
	Command* cmd = new Command();
	cmd->name = "echo";
	cmd->argc = 1;
	cmd->argv = new string[1];
	cmd->argv[0] = EchoCommand::text;
	return cmd;
}

HashCommand::HashCommand(char* path){
	HashCommand::path = path;
}

Command* HashCommand::ToStandartCommand(){
	Command* cmd = new Command();
	cmd->name = "hash";
	cmd->argc = 1;
	cmd->argv = new string[1];
	cmd->argv[0] = HashCommand::path;
	return cmd;
}

