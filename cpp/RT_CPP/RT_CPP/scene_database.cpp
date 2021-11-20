#include "scene_database.h"

using namespace scene_objects;

scene& scene_database::get_scene()
{
	return scn;
}

camera& scene_database::get_camera()
{
	return cam;
}

vector<shape&>& scene_database::get_shapes()
{
	return shapes;
}

void scene_database::set_scene(scene& sc)
{
	scn = sc;
}

void scene_database::set_camera(camera& c)
{
	cam = c;
}

void scene_database::set_shapes(vector<shape&>& shps)
{
	shapes = shps;
}