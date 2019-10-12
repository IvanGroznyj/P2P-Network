#include <iostream>
#include <fstream>
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

	std::map<std::string, std::string> hashTable;

public:
	char* GetFile(char* hash);
	unsigned long int GetHash(char* path);
	char* AddFile(char* path);

	void LoadHashTable();
};
