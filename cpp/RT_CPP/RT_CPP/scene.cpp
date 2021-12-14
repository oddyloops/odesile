#include "scene.h"
using namespace scene_objects;


int scene::get_height() const
{
	return height;
}

int scene::get_width() const
{
	return width;
}

vector3 scene::get_background() const
{
	return background;
}


vector3 scene::get_ambient_light() const
{
	return ambientLight;
}

void scene::set_ambient_light(vector3 amb)
{
	ambientLight = amb;
}

void scene::set_width(int w)
{
	width = w;
}

void scene::set_height(int h)
{
	height = h;
}

void scene::set_background(vector3 bg)
{
	background = bg;
}