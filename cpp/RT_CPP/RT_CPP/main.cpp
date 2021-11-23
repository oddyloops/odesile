#include "database_loader.h"
#include "renderer.h"
#include "image_generator.h"
#include <iostream>

using namespace utility::io;
using namespace utility;

int main(int charc,char** argv)
{
	
	char* filePath = argv[1];
	cout << "Loading scene from " << filePath << endl;
	scene_database* db = database_loader::load(filePath);
	renderer rend = renderer(*db);
	vector3** vect = rend.render();
	image_generator::write_pixels(vect,db->get_scene().get_width(),db->get_scene().get_height(),"img.bmp");
	delete db;
	delete vect;
	cout << "Done" << endl;
}