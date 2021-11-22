#include "database_loader.h"
#include <iostream>

using namespace utility::io;

int main(int charc,char** argv)
{
	
	char* filePath = argv[1];
	cout << "Loading scene from " << filePath << endl;
	scene_database* db = database_loader::load(filePath);
	delete db;
	cout << "Done" << endl;
}