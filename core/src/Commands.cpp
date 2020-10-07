/*
 *  Author: Ivan Khodyrev
 */
#include "Commands.h"

using namespace P2P_Network;

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

Hi_Command::Hi_Command():Command(Cmd_Hi){}
Echo_Command::Echo_Command(const char* text):Command(Cmd_Echo, text){}
Hash_Command::Hash_Command(const char* path):Command(Cmd_Hash, path){}
Get_File_Command::Get_File_Command(const char* hash):Command(Cmd_Get_File, hash){}
Get_Virtual_File_Command::Get_Virtual_File_Command(const char *filename):Command(Cmd_Get_Virtual_File, filename){}
Write_To_Virtual_File_Command::Write_To_Virtual_File_Command(const char *filename, const char *text){
	Command::name = Cmd_Write_To_Virtual_File;
	Command::argc = 2;
	Command::argv = new string[2];
	Command::argv[0] = filename;
	Command::argv[1] = text;
}
