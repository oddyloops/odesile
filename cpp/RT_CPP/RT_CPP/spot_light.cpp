#include "spot_light.h"
#include "operators.h"
#include <math.h>

using namespace utility;
using namespace lights;

<<<<<<< Updated upstream
spot_light::spot_light(int id, vector3 color, vector3 direction, vector3 o, float fall_of, float inner_angle, float outer_angle) : point_light(id, color, direction, o),
fall_of(fall_of)
{
	inner_angle_cos = cosf(0.5f * inner_angle);
	outer_angle_cos = cosf(0.5f * outer_angle);
=======
spot_light::spot_light(int id, vector3 color, vector3 direction, vector3 o, float fall_of) : point_light(id, color, direction, o),
fall_of(fall_of)
{
	inner_angle_cos = 
>>>>>>> Stashed changes
}

vector3 spot_light::get_color(vector3 point)const
{
	vector3 float_dir = get_direction(point);
	float alpha_cos = vector3::dot(float_dir, direction);

	if (alpha_cos > inner_angle_cos)
		return color;

	else if (alpha_cos < outer_angle_cos)
	{
		vector3 dark;
		dark.x = 0;
		dark.y = 0;
		dark.z = 0;
		return dark;
	}
		

	else
	{
		float fall = powf(((alpha_cos - outer_angle_cos) / (inner_angle_cos - outer_angle_cos)), fall_of);
		return fall * color;
	}
}