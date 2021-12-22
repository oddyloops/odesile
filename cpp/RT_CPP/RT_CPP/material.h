#pragma once
#include <vector>
#include "vector3.h"
#include "material_type.h"

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
		virtual vector3 get_ambient_color(int sid, vector3 v) const = 0;
		virtual vector3 get_diffuse_color(int sid, vector3 v) const = 0;
		virtual vector3 get_specular_color(int sid, vector3 v) const = 0;
		virtual float get_specularity(int sid, vector3 v) const = 0;
		virtual float get_reflectivity(int sid, vector3 v) const = 0;
		virtual float get_transparency(int sid, vector3 v) const = 0;
		virtual float get_refractive_index(int sid, vector3 v) const = 0;
	}; 
}
