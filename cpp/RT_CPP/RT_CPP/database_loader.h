#pragma once
#include <string>
#include "scene_database.h"
#include "sphere.h"
#include "rectangle.h"
#include "triangle.h"
#include "color_material.h"
#include "directional_light.h"
#include "point_light.h"
#include "spot_light.h"
#include "io/json.hpp"


using namespace std;
using namespace utility;
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
			static material_types int_to_enum(int type);
			static vector<vector3> parse_vector3_array(json const& j);
			static vector<float> parse_float_array(json const& j);
			static scene* load_scene(json const& j);
			static camera* load_camera(json const& j, int width, int height);

			static vector<shape*>* load_shapes(json const& j);
			static vector<sphere*>* load_spheres(json const& j);
			static sphere* load_sphere(json const& j);
			static vector<rectangle*>* load_rectangles(json const& j);
			static rectangle* load_rectangle(json const& j);
			static vector<triangle*>* load_triangles(json const& j);
			static triangle* load_triangle(json const& j);

			static vector<material*>* load_materials(json const& j);
			static vector<color_material*>* load_color_materials(json const& j);
			static color_material* load_color_material(json const& j);

			static vector<light*>* load_lights(json const& j);
			static vector<directional_light*>* load_directional_lights(json const& j);
			static directional_light* load_directional_light(json const& j);
			static vector<point_light*>* load_point_lights(json const& j);
			static point_light* load_point_light(json const& j);
			static vector<spot_light*>* load_spot_lights(json const& j);
			static spot_light* load_spot_light(json const& j);



		public:
			static scene_database* load(string file);
		};
	}
}
