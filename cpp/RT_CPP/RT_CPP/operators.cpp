#include "operators.h"
using namespace utility;

vector3 utility::operator / (vector3 const &myVector, float myFloat)
{
	vector3 vecs;
	vecs.x = myVector.x / myFloat;
	vecs.y = myVector.y / myFloat;
	vecs.z = myVector.z / myFloat;
	return vecs;
}


vector3 utility::operator - (vector3 const& v1, vector3 const& v2)
{
	vector3 vec;
	vec.x = v1.x - v2.x;
	vec.y = v1.y - v2.y;
	vec.z = v1.z - v2.z;
	return vec;
}

vector3 utility::operator + (vector3 const& v1, vector3 const& v2)
{
	vector3 vec;
	vec.x = v1.x + v2.x;
	vec.y = v1.y + v2.y;
	vec.z = v1.z + v2.z;
	return vec;
}

vector3 utility::operator * (vector3 const& v, float f)
{
	vector3 vec;
	vec.x = f * v.x;
	vec.y = f * v.y;
	vec.z = f * v.z;
	return vec;
}

vector3 utility::operator * (float f, vector3 const& v)
{
	vector3 vec;
	vec.x = f * v.x;
	vec.y = f * v.y;
	vec.z = f * v.z;
	return vec;
}

vector3 utility::operator * (vector3 const& v1, vector3 const& v2)
{
	vector3 vec;
	vec.x = v1.y * v2.z - v1.z * v2.y;
	vec.y = v1.z * v2.x - v1.x * v2.z;
	vec.z = v1.x * v2.y - v1.y * v2.x;
	return vec;
}


