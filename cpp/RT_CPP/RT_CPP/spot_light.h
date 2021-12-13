#pragma once
#include "light.h"
#include "point_light.h"


namespace lights
{
	class spot_light : public point_light
	{
	private:
		float inner_angle_cos, outer_angle_cos, fall_of;

	public:
		spot_light(int id, vector3 color, vector3 direction, vector3 o, float fall_of, float inner_angle, float outer_angle);
		vector3 get_color(vector3 point)const;
	};
}
