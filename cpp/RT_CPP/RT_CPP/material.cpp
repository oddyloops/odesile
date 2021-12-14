#include "material.h"

using namespace materials;


material::material(int mid, material_types tp, vector<float> specs)
	: id(mid),type(tp), specularities(specs)
{

}

int material::get_id() const
{
	return id;
}
