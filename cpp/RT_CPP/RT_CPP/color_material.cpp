#include "color_material.h"

using namespace materials;

vector3 color_material::get_ambient_color(shape* s, vector3 v) const
{
	return ambient_colors[0];
}

vector3 color_material::get_diffuse_color(shape* s, vector3 v) const
{
	return diffuse_colors[0];
}
vector3 color_material::get_specular_color(shape* s, vector3 v) const
{
	return specular_colors[0];
}
float color_material::get_specularity(shape* s, vector3 v) const
{
	return specularities[0];
}