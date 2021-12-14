#include "scene_database.h"

using namespace scene_objects;


scene& scene_database::get_scene()
{
	return *scn;
}

camera& scene_database::get_camera()
{
	return *cam;
}

vector<shape*>& scene_database::get_shapes()
{
	return *shapes;
}

vector<light*>& scene_database::get_lights()
{
	return *lights;
}

vector<material*>& scene_database::get_materials()
{
	return *materials;
}

void scene_database::set_scene(scene* sc)
{
	scn = sc;
}

void scene_database::set_camera(camera* c)
{
	cam = c;
}

void scene_database::set_shapes(vector<shape*>* shps)
{
	shapes = shps;
}

void scene_database::set_lights(vector<light*>* l)
{
	lights = l;
}

void scene_database::set_materials(vector<material*>* m)
{
	materials = m;
}


shape* scene_database::get_shape_by_id(int id)
{
	for (shape* s : *shapes)
	{
		if (s->get_id() == id)
		{
			return s;
		}
	}
	return nullptr;
}

material* scene_database::get_material_by_id(int id)
{
	for (material* m : *materials)
	{
		if (m->get_id() == id)
		{
			return m;
		}
	}
	return nullptr;
}

scene_database::~scene_database()
{
	delete scn;
	delete cam;
	for (int i = 0; i < shapes->size(); i++)
	{
		delete (*shapes)[i];
	}
	for (int i = 0; i < lights->size(); i++)
	{
		delete (*lights)[i];
	}
	for (int i = 0; i < materials->size(); i++)
	{
		delete (*materials)[i];
	}
	delete shapes;
	delete lights;
	delete materials;
}