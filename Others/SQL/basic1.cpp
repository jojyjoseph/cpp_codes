/*
 * An example to show sql can be integrated with C++
 * the ubuntu needs the following installations
 * 	sudo apt-get install libsqlite3-dev
 * 	sudo apt-get install sqlite3
 *
 * Compilation command : g++ -std=c++11 file.cpp -lsqlite3
 */

#include<iostream>
#include<sqlite3.h>

int main()
{
	sqlite3 * DB;
	int exit = 0;
	exit = sqlite3_open("example.db", &DB);

	if(exit){
		std::cerr<<"Error open DB " <<sqlite3_errmsg(DB) << std::endl;
		return -1;
	}
	else
		std::cout<<"Opened Database Successfully!"<<std::endl;
	
	sqlite3_close(DB);
	
	return 0;
}
