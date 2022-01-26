#include "color_material.h"

using namespace materials;

color_material::color_material(int mid, material_types tp, vector<vector3> acs,
	vector<vector3> dcs, vector<vector3> spcs, vector<float> specs,
	vector<float> rfs, vector<float> rts, vector<float> rfIs) : material(mid,tp,specs,rfs,rts, rfIs),
	ambient_colors(acs),diffuse_colors(dcs),specular_colors(spcs)
{

}

vector3 color_material::get_ambient_color(vector2 uv) const
{
	return ambient_colors[0];
}

vector3 color_material::get_diffuse_color(vector2 uv) const
{
	return diffuse_colors[0];
}
vector3 color_material::get_specular_color(vector2 uv) const
{
	return specular_colors[0];
}
float color_material::get_specularity(vector2 uv) const
{
	return specularities[0];
}

float color_material::get_reflectivity(vector2 uv) const
{
	return reflectivities[0];
}

float color_material::get_transparency(vector2 uv) const
{
	return transparencies[0];
}

float color_material::get_refractive_index(vector2 uv) const
{
	return refractiveIndices[0];
}