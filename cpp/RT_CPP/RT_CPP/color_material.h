#pragma once
#include <vector>
#include "vector3.h"
#include "material.h"

using namespace std;
using namespace utility;


namespace materials
{ 
	class color_material : public material 
	{
	private:
		vector<vector3> ambient_colors, diffuse_colors, specular_colors;
	
	public:
		color_material(int mid, material_types tp, vector<vector3> acs,
			vector<vector3> dcs,vector<vector3> spcs,vector<float> specs,
			vector<float> rfs, vector<float> rts, vector<float> rfIs);
		vector3 get_ambient_color(int sid, vector3 v) const;
		vector3 get_diffuse_color(int sid, vector3 v) const;
		vector3 get_specular_color(int sid, vector3 v) const;
		float get_specularity(int sid, vector3 v) const;
		float get_reflectivity(int sid, vector3 v) const;
		float get_transparency(int sid, vector3 v) const;
		float get_refractive_index(int sid, vector3 v) const;
	};

}

