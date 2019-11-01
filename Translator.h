#include "Commands.h"

class Translator {
private:
	const static char separator = '|';
public:
	char* CommandToText(Command *cmd);
	Command* TextToCommand(char* cmd_str);
};
