#pragma once
#include <vector>
#include "vector3.h"
#include "material.h"
#include "texture.h"

using namespace std;
using namespace utility;

namespace materials
{
	class texture_material : public material
	{
	private:
		vector<vector3> ambient_colors, specular_colors;
		vector<texture*>diffuse_colors;

	public:
		texture_material(int mid, material_types tp, vector<vector3> acs,
			vector<texture*> dcs, vector<vector3> spcs, vector<float> specs,
			vector<float> rfs, vector<float> rts, vector<float> rfIs);

		vector3 get_ambient_color(vector2 uv) const;
		vector3 get_diffuse_color(vector2 uv) const;
		vector3 get_specular_color(vector2 uv) const;
		float get_specularity(vector2 uv) const;
		float get_reflectivity(vector2 uv) const;
		float get_transparency(vector2 uv) const;
		float get_refractive_index(vector2 uv) const;
	};
}