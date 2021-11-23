#pragma once

#include <vector>
#include "scene_database.h"

using namespace scene_objects;
using namespace std;

namespace utility
{
	class renderer
	{
	private:
		scene_database& db;
		
		intersection_record* run_intersection(camera const& cam,vector<shape*> const& shapes, int pX, int pY);

	public:
		renderer(scene_database& db);

		vector3** render();
	};
}