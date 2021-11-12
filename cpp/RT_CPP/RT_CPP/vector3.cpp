#include "vector3.h"
#include "operators.h"
#include <math.h>
using namespace utility;

float vector3 ::magnitude () 
{
	float sumSquare = (x * x) + (y * y) + (z * z);
	return sqrtf(sumSquare);
}

vector3 vector3::normalize()
{
	float m = magnitude();
	return *this / m;
}