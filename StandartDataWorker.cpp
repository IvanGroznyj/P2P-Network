#include "MainInterfaces.h"
#include "StandartDataWorker.h"
#include <iostream>
#include <fstream>

char* StandartDataWorker::GetFile(char* hash){
	return "kek";
};

unsigned long int StandartDataWorker::GetHash(char* path){
		std::ifstream fout(path);
		std::string s;
		std::string sum = "";
		if(fout.is_open()){
					while(!fout.eof()){
						std::getline(fout,s);
						sum += s;
					}
					fout.close();
					return std::hash<std::string>{}(sum);
		}
		return -1;
	};

char* StandartDataWorker::AddFile(char* path){
	return "kek";
};





