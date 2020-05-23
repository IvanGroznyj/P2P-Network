/*
 *  Author: Ivan Khodyrev
 */
#include "../includes/Commands.h"

Command::Command(){
	Command::argc = 0;
	Command::name = '\0';
	Command::argv = nullptr;
}

Command::Command(char name){
	Command::argc = 0;
	Command::name = name;
	Command::argv = nullptr;
}

Command::Command(char name, const char* arg){
	Command::name = name;
	Command::argc = 1;
	Command::argv = new string[1];
	Command::argv[0] = arg;
}

HiCommand::HiCommand():Command(CmdHi){}
EchoCommand::EchoCommand(const char* text):Command(CmdEcho,text){}
HashCommand::HashCommand(const char* path):Command(CmdHash, path){}
GetFileCommand::GetFileCommand(const char* hash):Command(CmdGetFile, hash){}
GetVirtualFileCommand::GetVirtualFileCommand(const char *filename):Command(CmdGetVirtualFile, filename){};
WriteToVirtualFileCommand::WriteToVirtualFileCommand(const char *filename, const char *text){
	Command::name = CmdWriteToVirtualFile;
	Command::argc = 2;
	Command::argv = new string[2];
	Command::argv[0] = filename;
	Command::argv[1] = text;
}
