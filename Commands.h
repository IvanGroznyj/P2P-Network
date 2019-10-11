#include <cstring>
#include <iostream>
using namespace std;

struct Command{
	string name;
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
