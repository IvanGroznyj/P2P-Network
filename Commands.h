#include <cstring>
#include <iostream>
using namespace std;

enum CommandsIndexes{CmdEcho=1, CmdHi ,CmdHash};
//char* CommandsNames[];
//int CommandsCount;

struct Command{
	char name;
	int argc;
	string* argv;
};

struct ICommand{
	virtual Command* ToStandartCommand()=0;
};

struct HiCommand: public ICommand{
	HiCommand();
	Command* ToStandartCommand();
};

struct EchoCommand: public ICommand{
	EchoCommand(char* text);
	Command* ToStandartCommand();
private:
	string text;
};

struct HashCommand: public ICommand{
	HashCommand(char* path);
	Command* ToStandartCommand();
private:
	string path;
};
