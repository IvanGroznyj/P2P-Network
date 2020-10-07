/*
 *  Author: Ivan Khodyrev
 */
#include "MainInterfaces.h"
#include "StandartDataWorker.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <dirent.h>

#include <sstream>

using namespace std;
using namespace P2P_Network;

char* Standart_Data_Worker::get_File(const char* hash){
	string path = Standart_Data_Worker::hash_table[hash];
	return Standart_Data_Worker::get_File_By_Name(path.c_str());
};

char* Standart_Data_Worker::get_File_By_Name(const char *name){
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

unsigned long int Standart_Data_Worker::get_Hash(const char* path){
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

char* Standart_Data_Worker::add_File(const char* path){
	return "kek";
};

void Standart_Data_Worker::load_Hash_Table(){
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
		tmp = to_string(Standart_Data_Worker::get_Hash(current_file.str().c_str()));
		Standart_Data_Worker::hash_table[tmp] = current_file.str();
		current_file.str("data/");
	}
}

void Standart_Data_Worker::append_To_File_By_Name(const char* name, const char* text){
	ofstream file_out;
	try{
		file_out.open(name, ios_base::app);
		file_out<<text;
	}catch(...){
		printf("Can't write to the file");
	}
	if(file_out.is_open()) file_out.close();
}




