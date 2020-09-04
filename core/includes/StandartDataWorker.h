/*
 *  Author: Ivan Khodyrev
 */

#ifndef StandartDataWorker_H
#define StandartDataWorker_H

#include <iostream>
#include <map>

class StandartDataWorker: public IDataWorker{
private:
	struct MyHash
	{
	    std::size_t operator()(std::string &data) const noexcept
	    {
	        std::size_t h1 = std::hash<std::string>{}(data);
	        return h1;
	    }
	};

	std::map<std::string, std::string> hash_table;

public:
	char* GetFile(const char* hash);
	unsigned long int GetHash(const char* path);
	char* AddFile(const char* path);
	char* GetFileByName(const char* name);
	void AppendToFileByName(const char* name, const char* text);
	void LoadHashTable();
};

#endif