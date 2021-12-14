#pragma once
#include "scene.h"
#include "camera.h"
#include "shape.h"
#include <vector>

using namespace cameras;
using namespace shapes;
using namespace std;

namespace scene_objects
{
	class scene_database
	{
	private:
		scene* scn;
		camera* cam;
		vector<shape*>* shapes;
		vector<light*>* lights;
		vector<material*>* materials;
	public:

		~scene_database();

		scene& get_scene();

		camera& get_camera();

		vector<shape*>& get_shapes();

		vector<light*>& get_lights();

		vector<material*>& get_materials();

		shape* get_shape_by_id(int id);

		material* get_material_by_id(int id);

		void set_scene(scene* sc);

		void set_camera(camera* c);
		
		void set_shapes(vector<shape*>* shps);

		void set_lights(vector<light*>* l);

		void set_materials(vector<material*>* m);


	};
}