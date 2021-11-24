#include "triangle.h"
#include "operators.h"
#include <math.h>
#include <cfloat>
using namespace shapes;

triangle::triangle(int id, vector3 a, vector3 b, vector3 c) : shape(id),
vertexA(a), vertexB(b), vertexC(c)
{
	vector3 ab = vertexB - vertexA;
	vector3 ac = vertexC - vertexA;
	normal = (ac * ab).normalize();
	d = vertexA.magnitude();
}

intersection_record* triangle::ray_plane_intersection(ray r)
{
	intersection_record* rec = new intersection_record;
	
	float dot = vector3::dot(r.direction, normal);
	if (fabsf(dot) < FLT_EPSILON)
	{
		return rec; // parallel to the plane, no intersection
	}
	float dist = (-(vector3::dot(normal, r.position) + d)) / dot;
	
	if (dist > 0)
	{
		rec->distance = dist;
		rec->hit = true;
		rec->point = r.position + dist * r.direction;
	}

	return rec;
	
}