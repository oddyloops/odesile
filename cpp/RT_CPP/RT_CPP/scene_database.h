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
		scene& scn;
		camera& cam;
		vector<shape&>& shapes;
	public:
		scene& get_scene();

		camera& get_camera();

		vector<shape&>& get_shapes();

		void set_scene(scene& sc);

		void set_camera(camera& c);
		
		void set_shapes(vector<shape&>& shps);

	};
}