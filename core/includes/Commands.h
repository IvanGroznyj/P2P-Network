/*
 *  Author: Ivan Khodyrev
 */

#ifndef Commands_H
#define Commands_H

#include <iostream>
using namespace std;

namespace P2P_Network{

	enum Commands_Indexes{Cmd_Echo=1, Cmd_Hi ,Cmd_Hash, Cmd_Add_Me, Cmd_Get_File, Cmd_Get_Virtual_File, Cmd_Write_To_Virtual_File, Cmd_Append_To_Virtual_File};

	struct Command{
		Command();
		Command(char name);
		Command(char name, string arg);
		Command(string str);
		string to_str();
		char name;
		int argc;
		string* argv;
	};

	struct Hi_Command: public Command{
		Hi_Command();
	};

	struct Echo_Command: public Command{
		Echo_Command(string text);
	};

	struct Hash_Command: public Command{
		Hash_Command(string path);
	};

	struct Get_File_Command: public Command{
		Get_File_Command(string hash);
	};

	struct Get_Virtual_File_Command: public Command{
		Get_Virtual_File_Command(string filename);
	};

	struct Write_To_Virtual_File_Command: public Command{
		Write_To_Virtual_File_Command(string filename, string text);
	};

	struct Append_To_Virtual_File_Command: public Command{
		Append_To_Virtual_File_Command(string filename, string text);
	};

	struct Add_Me_Command: public Command{
		Add_Me_Command(string addr);
	};

}

#endif