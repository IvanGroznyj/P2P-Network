#include "MainInterfaces.h"
#include "StandartDataWorker.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <dirent.h>
using namespace std;

char* StandartDataWorker::GetFile(char* hash){
	std::string path = StandartDataWorker::hash_table[hash];
	return StandartDataWorker::GetFileByName((char*)path.c_str());
};

char* StandartDataWorker::GetFileByName(char *name){
	std::ifstream file_in(name);
	std::string buffer_str;
	std::string sum_str = "";
	bool is_row_end = false;
	if(file_in.is_open()){
		while(!file_in.eof()){
			if (is_row_end){
				sum_str+='\n';
			}else{
				is_row_end = true;
			}
			std::getline(file_in,buffer_str);
			sum_str += buffer_str;
		}
		file_in.close();
		char *result_buffer = new char[sum_str.size()+1];
		strcpy(result_buffer, sum_str.c_str());
		return result_buffer;
	}
	return "File can't open";
}

unsigned long int StandartDataWorker::GetHash(const char* path){
	std::ifstream file_in(path);
	std::string buffer_str;
	std::string sum_str = "";
	if(file_in.is_open()){
		while(!file_in.eof()){
			std::getline(file_in,buffer_str);
			sum_str += buffer_str;
		}
		file_in.close();
		return std::hash<std::string>{}(sum_str);
	}
	return -1;
};

char* StandartDataWorker::AddFile(char* path){
	return "kek";
};

void StandartDataWorker::LoadHashTable(){
	DIR *dp;
	dirent *d;
	dp = opendir("data");
	string tmp;
	string current_file = "data/";
	while((d = readdir(dp)) != NULL)
	{
		if(!strcmp(d->d_name,".") || !strcmp(d->d_name,".."))
			continue;

		current_file += d->d_name;
		tmp = to_string(StandartDataWorker::GetHash(current_file.c_str()));
		char p[tmp.size()+1];
		strcpy(p, tmp.c_str());
		StandartDataWorker::hash_table[p] = "data/firstfile.txt";
		current_file = "data/";
	}
}

void StandartDataWorker::AppendToFileByName(char* name, char* text){
	std::ofstream file_out;
	try{
		file_out.open(name, std::ios_base::app);
		file_out<<text;
	}catch(...){
		printf("Can't write to the file");
	}
	if(file_out.is_open()) file_out.close();
}




