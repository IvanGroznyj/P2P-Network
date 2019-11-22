/*
 *  Author: Ivan Khodyrev
 */
#include <iostream>
using namespace std;

enum CommandsIndexes{CmdEcho=1, CmdHi ,CmdHash, CmdGetFile, CmdGetVirtualFile, CmdWriteToVirtualFile};

struct Command{
	Command();
	Command(char name);
	Command(char name, const char* arg);
	char name;
	int argc;
	string* argv;
};

struct HiCommand: public Command{
	HiCommand();
};

struct EchoCommand: public Command{
	EchoCommand(const char* text);
};

struct HashCommand: public Command{
	HashCommand(const char* path);
};

struct GetFileCommand: public Command{
	GetFileCommand(const char* hash);
};

struct GetVirtualFileCommand: public Command{
	GetVirtualFileCommand(const char* filename);
};
struct WriteToVirtualFileCommand: public Command{
	WriteToVirtualFileCommand(const char* filename, const char* text);
};
