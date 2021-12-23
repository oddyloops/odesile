#include "directional_light.h"
#include <cfloat>

using namespace lights;


directional_light::directional_light(int id, vector3 color, vector3 direction) : light(id, color, direction)
{

}
vector3 directional_light :: get_direction (vector3 coordinate) const
{
	return direction;
}

float directional_light::light_point_distance(vector3 point)const
{
	return FLT_MAX;
}