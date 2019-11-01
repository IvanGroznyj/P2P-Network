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
	char* GetFile(char* hash);
	unsigned long int GetHash(char* path);
	char* AddFile(char* path);
	char* GetFileByName(char* name);
	void AppendToFileByName(char* name, char* text);
	void LoadHashTable();
};
