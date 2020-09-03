/*
 *  Author: Ivan Khodyrev
 */
#include "../includes/MainInterfaces.h"
#include "../includes/StandartDataWorker.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <dirent.h>

#include <sstream>

using namespace std;

char* StandartDataWorker::GetFile(const char* hash){
	string path = StandartDataWorker::hash_table[hash];
	return StandartDataWorker::GetFileByName(path.c_str());
};

char* StandartDataWorker::GetFileByName(const char *name){
	ifstream file_in(name, ios::binary);
	string buffer_str;
	stringstream sum_str;
	sum_str << "";
	bool is_row_end = false;
	if(file_in.is_open()){
		while(!file_in.eof()){
			if (is_row_end){
				sum_str << '\n';
			}else{
				is_row_end = true;
			}
			getline(file_in,buffer_str);
			sum_str << buffer_str;
		}
		file_in.close();
		char *result_buffer = new char[sum_str.str().size()+1];
		strcpy(result_buffer, sum_str.str().c_str());
		return result_buffer;
	}
	return "File can't open";
}

unsigned long int StandartDataWorker::GetHash(const char* path){
	ifstream file_in(path, ios::binary);
	string buffer_str;
	stringstream sum_str;
	sum_str << "";
	if(file_in.is_open()){
		while(!file_in.eof()){
			getline(file_in,buffer_str);
			sum_str << buffer_str;
		}
		file_in.close();
		return std::hash<string>{}(sum_str.str());
	}
	return -1;
};

char* StandartDataWorker::AddFile(const char* path){
	return "kek";
};

void StandartDataWorker::LoadHashTable(){
	DIR *dp;
	dirent *d;
	dp = opendir("data");
	string tmp;
	stringstream current_file;
	current_file << "data/";
	while((d = readdir(dp)) != NULL)
	{
		if(!strcmp(d->d_name,".") || !strcmp(d->d_name,".."))
			continue;

		current_file << d->d_name;
		tmp = to_string(StandartDataWorker::GetHash(current_file.str().c_str()));
		StandartDataWorker::hash_table[tmp] = current_file.str();
		current_file.str("data/");
	}
}

void StandartDataWorker::AppendToFileByName(const char* name, const char* text){
	ofstream file_out;
	try{
		file_out.open(name, ios_base::app);
		file_out<<text;
	}catch(...){
		printf("Can't write to the file");
	}
	if(file_out.is_open()) file_out.close();
}




