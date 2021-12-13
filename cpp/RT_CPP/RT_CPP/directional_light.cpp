#include "directional_light.h"

using namespace lights;


directional_light::directional_light(int id, vector3 color, vector3 direction) : light(id, color, direction)
{

}
vector3 directional_light :: get_direction (vector3 coordinate) const
{
	return direction;
}