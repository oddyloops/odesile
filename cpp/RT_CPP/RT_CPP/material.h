#pragma once
#include <vector>
#include "vector3.h"
#include "material_type.h"
#include "vector2.h"

using namespace std;
using namespace utility;


namespace materials
{
	class material
	{
	protected:
		int id;
		material_types type;
		vector<float> specularities,reflectivities, transparencies, refractiveIndices;

	public:
		material(int mid, material_types tp, vector<float> specs, vector<float> rfs, vector<float> rts, vector<float> rfIs);
		int get_id() const;
		virtual vector3 get_ambient_color(vector2 uv) const = 0;
		virtual vector3 get_diffuse_color(vector2 uv) const = 0;
		virtual vector3 get_specular_color(vector2 uv) const = 0;
		virtual float get_specularity(vector2 uv) const = 0;
		virtual float get_reflectivity(vector2 uv) const = 0;
		virtual float get_transparency(vector2 uv) const = 0;
		virtual float get_refractive_index(vector2 uv) const = 0;
	}; 
}
