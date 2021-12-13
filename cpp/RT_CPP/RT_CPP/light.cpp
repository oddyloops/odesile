#include "light.h"

using namespace lights;

light::light(int id, vector3 color, vector3 direction) :
	id(id), color(color), direction(direction.normalize())
{

}

vector3 light::get_color(vector3 point)const
{
	return color;
}