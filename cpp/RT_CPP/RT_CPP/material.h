#pragma once
#include <vector>
#include "vector3.h"
#include "shape.h"

using namespace shapes;
using namespace std;
using namespace utility;


namespace materials
{
	class material
	{
	protected:
		int id;
		enum material_types {SOLID, GRADIENT, CHECKERED, STRIPE};
		vector<float> specularities;

	public:
		virtual vector3 get_ambient_color(shape* s, vector3 v) const = 0;
		virtual vector3 get_diffuse_color(shape* s, vector3 v) const = 0;
		virtual vector3 get_specular_color(shape* s, vector3 v) const = 0;
		virtual float get_specularity(shape* s, vector3 v) const = 0;
	};
}
