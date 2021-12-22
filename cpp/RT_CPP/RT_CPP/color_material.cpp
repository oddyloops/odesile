#include "color_material.h"

using namespace materials;

color_material::color_material(int mid, material_types tp, vector<vector3> acs,
	vector<vector3> dcs, vector<vector3> spcs, vector<float> specs,
	vector<float> rfs, vector<float> rts, vector<float> rfIs) : material(mid,tp,specs,rfs,rts, rfIs),
	ambient_colors(acs),diffuse_colors(dcs),specular_colors(spcs)
{

}

vector3 color_material::get_ambient_color(int sid, vector3 v) const
{
	return ambient_colors[0];
}

vector3 color_material::get_diffuse_color(int sid, vector3 v) const
{
	return diffuse_colors[0];
}
vector3 color_material::get_specular_color(int sid, vector3 v) const
{
	return specular_colors[0];
}
float color_material::get_specularity(int sid, vector3 v) const
{
	return specularities[0];
}

float color_material::get_reflectivity(int sid, vector3 v) const
{
	return reflectivities[0];
}

float color_material::get_transparency(int sid, vector3 v) const
{
	return transparencies[0];
}

float color_material::get_refractive_index(int sid, vector3 v) const
{
	return refractiveIndices[0];
}