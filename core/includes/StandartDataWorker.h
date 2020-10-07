/*
 *  Author: Ivan Khodyrev
 */

#ifndef StandartDataWorker_H
#define StandartDataWorker_H

#include <iostream>
#include <map>

namespace P2P_Network{

	class Standart_Data_Worker: public I_Data_Worker{
	private:
		struct My_Hash
		{
		    std::size_t operator()(std::string &data) const noexcept
		    {
		        std::size_t h1 = std::hash<std::string>{}(data);
		        return h1;
		    }
		};

		std::map<std::string, std::string> hash_table;

	public:
		char* get_File(const char* hash);
		unsigned long int get_Hash(const char* path);
		char* add_File(const char* path);
		char* get_File_By_Name(const char* name);
		void append_To_File_By_Name(const char* name, const char* text);
		void load_Hash_Table();
	};

}

#endif