#include "operators.h"
using namespace utility;

vector3 operator / (vector3 const &myVector, float myFloat)
{
	vector3 vecs;
	vecs.x = myVector.x / myFloat;
	vecs.y = myVector.y / myFloat;
	vecs.z = myVector.z / myFloat;
	return vecs;
}