#include "vector3.h"
#include "operators.h"
#include <math.h>
using namespace utility;

float vector3::magnitude_sq()
{
	return (x * x) + (y * y) + (z * z);
}


float vector3 ::magnitude () 
{
	return sqrtf(magnitude_sq());
}

vector3 vector3::clamp()
{
	return { fmaxf(0,fminf(x,1)), fmaxf(0,fminf(y,1)) , fmaxf(0,fminf(z,1)) };
}

vector3 vector3::normalize()
{
	float m = magnitude();
	return *this / m;
}

float vector3::dot(vector3 a, vector3 b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

vector3 vector3::mult(vector3 a, vector3 b)
{
	return { a.x * b.x,a.y * b.y,a.z * b.z };
}