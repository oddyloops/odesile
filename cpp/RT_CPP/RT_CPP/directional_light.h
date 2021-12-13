#pragma once
#include "light.h"


namespace lights
{
	class directional_light : public light
	{
	public:
		directional_light(int id, vector3 color, vector3 direction);
		vector3 get_direction(vector3 coordinate)const;
	};
}