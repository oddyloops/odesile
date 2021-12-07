#include "triangle.h"
#include "operators.h"
#include <math.h>
#include <cfloat>
using namespace shapes;

triangle::triangle(int id, vector3 a, vector3 b, vector3 c) : shape(id),
vertexA(a), vertexB(b), vertexC(c)
{
	ab = vertexB - vertexA;
	ac = vertexC - vertexA;
	bc = vertexC - vertexB;
	normal = (ac * ab).normalize();
	area = triangle_area(ab, ac, vertexA, vertexB);
	d = vertexA.magnitude();
}

float triangle::triangle_area(vector3 ab,  vector3 ac,vector3 vA, vector3 vB)
{
	vector3 normAb = ab.normalize();
	vector3 normAc = ac.normalize();
	float cosTheta = vector3::dot(normAb, normAc);
	float hypothenuse = ab.magnitude();
	float adj = hypothenuse * cosTheta;
	vector3 adjEnd = vA + adj * normAc;
	float height = (vB - adjEnd).magnitude();
	return 0.5f * ac.magnitude() * height;
}

intersection_record* triangle::ray_plane_intersection(ray r) const
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

void triangle::intersect(ray r, intersection_record& rec) const
{
	intersection_record* ray_int = ray_plane_intersection(r);
	if (ray_int->hit)
	{
		//computing barymetric area ratios
		float areaAlpha = triangle_area(ray_int->point - vertexB, vertexA - vertexB, vertexB, ray_int->point) /area;
		float areaBeta = triangle_area(ray_int->point - vertexC, vertexB - vertexC, vertexC, ray_int->point) / area;
		float areaGamma = triangle_area(ray_int->point - vertexA, ac, vertexA, ray_int->point) /area;

		float sum = areaAlpha + areaBeta + areaGamma;
		if (fabsf(1 - sum) < FLT_EPSILON) 
		{
			if (ray_int->distance < rec.distance)
			{
				rec.hit = true;
				rec.distance = ray_int->distance;
				rec.shape_id = id;
				rec.point = ray_int->point;
			}
		}
	}
}