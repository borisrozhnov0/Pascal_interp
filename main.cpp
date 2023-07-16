#include <iostream>
#include <string>
#include "inc/parser.hpp"
#include "inc/error.hpp"

using namespace std;

int main(int argv, char * argc[])
{
	std::string file_path;
	//init block
	if (argv!=2) {
		cout<< ERR_START_PAR;
		cin >> file_path;
	}
	else
		file_path = argc[1];
	Pascal_Parser pp(file_path);	
	return 0;
}
