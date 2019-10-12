#include "MainInterfaces.h"
#include "StandartDataWorker.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <dirent.h>

char* StandartDataWorker::GetFile(char* hash){
	std::string path = StandartDataWorker::hashTable[hash];
	std::ifstream fout(path.c_str());
	std::string s;
	std::string sum = "";
	bool flag = false;
	if(fout.is_open()){
		while(!fout.eof()){
			if (flag){
				sum+='\n';
			}else{
				flag = true;
			}
			std::getline(fout,s);
			sum += s;
		}
		fout.close();
		char *res = new char[sum.size()+1];
		strcpy(res, sum.c_str());
		return res;
	}
	return "File can't open";
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

void StandartDataWorker::LoadHashTable(){
	std::string tmp = std::to_string(StandartDataWorker::GetHash("data/firstfile.txt"));
	char p[tmp.size()+1];
	strcpy(p, tmp.c_str());
	StandartDataWorker::hashTable[p] = "data/firstfile.txt";
	StandartDataWorker::hashTable["13008458447081099134"] = "../sem2.cpp";
	printf("find: %s - %s\n", "data/firstfile.txt", p);
}




