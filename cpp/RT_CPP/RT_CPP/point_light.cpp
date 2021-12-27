#include "point_light.h"
#include "operators.h"

using namespace utility;
using namespace lights;

point_light::point_light(int id, vector3 color, vector3 direction, vector3 o) : light(id, color, direction),
origin(o)
{

}

vector3 point_light::get_direction(vector3 coordinate) const
{
	return (coordinate - origin).normalize();
}

float point_light::light_point_distance(vector3 point)const
{
	return(point - origin).magnitude_sq();
}
