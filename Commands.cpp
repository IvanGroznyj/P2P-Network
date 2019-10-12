#include "Commands.h"

//enum CommandsIndexes{CmdEcho, CmdHi ,CmdHash};
//char* CommandsNames[]{"echo", "hi", "hash"};
//int CommandsCount = sizeof(CommandsNames);

HiCommand::HiCommand(){}

Command* HiCommand::ToStandartCommand(){
	Command* cmd = new Command();
	cmd->name = CmdHi;
	cmd->argc = 0;
	cmd->argv = nullptr;
	return cmd;
}

EchoCommand::EchoCommand(char* text){
	EchoCommand::text = text;
}

Command* EchoCommand::ToStandartCommand(){
	Command* cmd = new Command();
	cmd->name = CmdEcho;
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
	cmd->name = CmdHash;
	cmd->argc = 1;
	cmd->argv = new string[1];
	cmd->argv[0] = HashCommand::path;
	return cmd;
}

GetFileCommand::GetFileCommand(char *hash){
	GetFileCommand::hash = hash;
}

Command* GetFileCommand::ToStandartCommand(){
	Command* cmd = new Command();
	cmd->name = CmdGetFile;
	cmd->argc = 1;
	cmd->argv = new string[1];
	cmd->argv[0] = GetFileCommand::hash;
	return cmd;
}

