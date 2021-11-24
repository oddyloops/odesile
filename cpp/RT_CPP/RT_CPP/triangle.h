#pragma once
#include "shape.h"
#include "vector3.h"
using namespace utility;
namespace shapes
{
	class triangle : public shape
	{
	protected:
		vector3 vertexA;
		vector3 vertexB;
		vector3 vertexC;
		
		vector3 normal;
		float d;
	public:
		triangle(int id, vector3 a, vector3 b, vector3 c);
		intersection_record* ray_plane_intersection(ray r);
	};
}