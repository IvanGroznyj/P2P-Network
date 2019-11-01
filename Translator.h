#include "Commands.h"

class Translator {
private:
	char separator = '|';
public:
	char* CommandToText(Command *cmd);
	Command* TextToCommand(char* cmd_str);
};
