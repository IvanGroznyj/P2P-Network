#include <iostream>
using namespace std;

enum CommandsIndexes{CmdEcho=1, CmdHi ,CmdHash, CmdGetFile, CmdGetVirtualFile, CmdWriteToVirtualFile};

struct Command{
	Command();
	Command(char name);
	Command(char name, char* arg);
	char name;
	int argc;
	string* argv;
};

struct HiCommand: public Command{
	HiCommand();
};

struct EchoCommand: public Command{
	EchoCommand(char* text);
};

struct HashCommand: public Command{
	HashCommand(char* path);
};

struct GetFileCommand: public Command{
	GetFileCommand(char* hash);
};

struct GetVirtualFileCommand: public Command{
	GetVirtualFileCommand(char* filename);
};
struct WriteToVirtualFileCommand: public Command{
	WriteToVirtualFileCommand(char* filename, char* text);
};
