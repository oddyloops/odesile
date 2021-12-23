#pragma once
#include "light.h"


namespace lights
{
	class point_light : public light
	{
	protected:
		vector3 origin;

	public:
		point_light(int id, vector3 color, vector3 direction, vector3 o);
		vector3 get_direction(vector3 coordinate)const;
		float light_point_distance(vector3 point)const;
	};
}