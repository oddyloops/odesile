#pragma once
#include "vector3.h"

namespace utility 
{
	vector3 operator / (vector3 const &myVector, float myFloat);

	vector3 operator - (vector3 const& v1, vector3 const& v2);

	vector3 operator + (vector3 const& v1, vector3 const& v2);

	vector3 operator * (vector3 const& v, float f);

	vector3 operator * (float f, vector3 const& v);

	vector3 operator * (vector3 const& v1, vector3 const& v2);
}