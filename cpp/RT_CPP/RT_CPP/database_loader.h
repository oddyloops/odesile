#pragma once
#include <string>
#include "io/json.hpp"
#include "scene_database.h"
#include "sphere.h"

using namespace std;
using namespace scene_objects;

using namespace nlohmann;

namespace utility
{
	namespace io
	{
		class database_loader
		{
		private:
			static vector3 parse_vector3(string vectorStr);
			static scene* load_scene(json const& j);
			static camera* load_camera(json const& j, int width, int height);
			static vector<sphere*>* load_spheres(json const& j);
			static sphere* load_sphere(json const& j);
		public:
			static scene_database* load(string file);
		};
	}
}
