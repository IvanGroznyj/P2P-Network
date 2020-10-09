/*
 *  Author: Ivan Khodyrev
 */
#include "Commands.h"

#include <cstring>
#include <sstream>
#include <vector>

using namespace std;
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

Command::Command(char name, string arg){
	Command::name = name;
	Command::argc = 1;
	Command::argv = new string[1];
	Command::argv[0] = arg;
}

Command::Command(string str){
	Command::name = str[0];

	int start_pos, end_pos;
	start_pos = str.find("|");
	vector<string> args;

	if (start_pos != string::npos){
		start_pos++;
		end_pos = str.find("|", start_pos);

		while(end_pos != string::npos){
			args.push_back(str.substr(start_pos, end_pos - start_pos));
			start_pos = end_pos + 1;
			end_pos = str.find("|", start_pos);		
		}
		args.push_back(str.substr(start_pos));
	}
	
	Command::argc = args.size();
	Command::argv = new string[Command::argc];
	for(int i=0; i < Command::argc; i++){
		Command::argv[i] = args[i];
	}
}

string Command::to_str(){
	stringstream sum_str;
	sum_str << "";
	sum_str << Command::name;
	for(int i=0; i < Command::argc; i++){
		sum_str << '|' << (Command::argv)[i];
	}
	return sum_str.str();
}

Hi_Command::Hi_Command():Command(Cmd_Hi){}
Echo_Command::Echo_Command(string text):Command(Cmd_Echo, text){}
Hash_Command::Hash_Command(string path):Command(Cmd_Hash, path){}
Add_Me_Command::Add_Me_Command(string addr):Command(Cmd_Add_Me, addr){}
Get_File_Command::Get_File_Command(string hash):Command(Cmd_Get_File, hash){}
Get_Virtual_File_Command::Get_Virtual_File_Command(string filename):Command(Cmd_Get_Virtual_File, filename){}
Write_To_Virtual_File_Command::Write_To_Virtual_File_Command(string filename, string text){
	Command::name = Cmd_Write_To_Virtual_File;
	Command::argc = 2;
	Command::argv = new string[2];
	Command::argv[0] = filename;
	Command::argv[1] = text;
}
Append_To_Virtual_File_Command::Append_To_Virtual_File_Command(string filename, string text){
	Command::name = Cmd_Append_To_Virtual_File;
	Command::argc = 2;
	Command::argv = new string[2];
	Command::argv[0] = filename;
	Command::argv[1] = text;
}
