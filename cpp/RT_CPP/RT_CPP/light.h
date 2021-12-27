#pragma once
#include "vector3.h"

using namespace utility;
using namespace std;

namespace lights
{
	class light
	{
	protected:
		int id;
		vector3 color, direction;

	public:
		virtual vector3 get_direction(vector3 coordinate)const = 0;
		virtual vector3 get_color(vector3 point)const;
		virtual float light_point_distance(vector3 point)const = 0;
		light(int id, vector3 color, vector3 direction);
	};
}
