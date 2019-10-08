#include <cstring>
#include <iostream>
using namespace std;

struct Command{
	string name;
	int argc;
	string* argv;
};

class Translator {
public:
	char* CommandToText(Command *cmd);
	Command* TextToCommand(char* txtcmd);
};
