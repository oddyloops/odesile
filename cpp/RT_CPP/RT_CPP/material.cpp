#include "material.h"

using namespace materials;


material::material(int mid, material_types tp, vector<float> specs, vector<float> rfs, vector<float> rts, vector<float> rfIs)
	: id(mid),type(tp), specularities(specs), reflectivities(rfs), transparencies(rts), refractiveIndices(rfIs)
{

}

int material::get_id() const
{
	return id;
}
