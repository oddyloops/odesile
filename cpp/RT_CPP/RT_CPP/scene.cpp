#include "scene.h"
using namespace scene_objects;


int scene::get_height()
{
	return height;
}

int scene::get_width()
{
	return width;
}

vector3 scene::get_background()
{
	return background;
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