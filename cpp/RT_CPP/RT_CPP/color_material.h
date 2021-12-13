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
		vector3 get_ambient_color(shape* s, vector3 v) const;
		vector3 get_diffuse_color(shape* s, vector3 v) const;
		vector3 get_specular_color(shape* s, vector3 v) const;
		float get_specularity(shape* s, vector3 v) const;
	};

}

