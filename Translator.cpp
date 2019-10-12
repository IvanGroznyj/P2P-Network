#include "Translator.h"
#include <cstring>

char* Translator::CommandToText(Command* cmd){
	string res = "";
	res += cmd->name;
	for(int i=0; i < cmd->argc; i++){
		res += '|'+(cmd->argv)[i];
	}
	//res+='\0';
	char *resc = new char[res.size()+1];
	strcpy(resc, res.c_str());
	return resc;
}

Command* Translator::TextToCommand(char* txtcmd){
	Command *res = new Command();
	char *c = txtcmd;
	res->name = txtcmd[0];
	res->argc = 0;
	while(*c!='\0'){
		if(*c=='|') (res->argc)++;
		c++;
	}
	c=txtcmd;
	/*
	while(*c!='|' && *c!='\0'){
		res->name += *c;
		c++;
	}*/
	c++;
	res->argv = new string[res->argc];
	for(int i=0; i < (res->argc); i++){
		c++;
		(res->argv)[i] = "";
		while(*c!='|' && *c!='\0'){
			(res->argv)[i] += *c;
			c++;
		}
	}
	return res;
}
