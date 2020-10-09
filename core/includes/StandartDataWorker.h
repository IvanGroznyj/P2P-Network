/*
 *  Author: Ivan Khodyrev
 */

#ifndef StandartDataWorker_H
#define StandartDataWorker_H

#include <iostream>
#include <map>

using namespace std;

namespace P2P_Network{

	class Standart_Data_Worker: public I_Data_Worker{
	private:
		struct My_Hash
		{
		    size_t operator()(string &data) const noexcept
		    {
		        size_t h1 = hash<string>{}(data);
		        return h1;
		    }
		};

		map<string, string> hash_table;

	public:
		string get_File(string hash);
		unsigned long int get_Hash(string path);
		string add_File(string path);
		string get_File_By_Name(string name);
		void append_To_File_By_Name(string name, string text);
		void load_Hash_Table();
	};

}

#endif