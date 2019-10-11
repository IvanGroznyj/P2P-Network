#include "Commands.h"

class Translator {
public:
	char* CommandToText(Command *cmd);
	Command* TextToCommand(char* txtcmd);
};
