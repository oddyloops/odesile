#include "triangle.h"
#include "operators.h"
#include <math.h>
#include <cfloat>
using namespace shapes;

triangle::triangle(int id,int mid, vector3 a, vector3 b, vector3 c) : shape(id,mid),
vertexA(a), vertexB(b), vertexC(c)
{
	ab = vertexB - vertexA;
	ac = vertexC - vertexA;
	bc = vertexC - vertexB;
	normal = (ac * ab).normalize();
	area = simpler_triangle_area(ab, ac);
	d = vertexA;
	float acMag = ac.magnitude();
	u_top = vector3::dot(ab, ac / acMag) / acMag;
}

float triangle::simpler_triangle_area(vector3 ab, vector3 ac)
{
	return 0.5f * (ab * ac).magnitude();
}

intersection_record* triangle::ray_plane_intersection(ray r) const
{
	intersection_record* rec = new intersection_record;
	
	float dot = vector3::dot(r.direction, normal);
	if (fabsf(dot) < FLT_EPSILON)
	{
		return rec; // parallel to the plane, no intersection
	}
	float dist = (vector3::dot(normal,d - r.position)) / dot;
	
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
	if (id == rec.except_id)
	{
		return;
	}
	intersection_record* ray_int = ray_plane_intersection(r);
	if (ray_int->hit)
	{
		//computing barymetric area ratios
		float areaAlpha = simpler_triangle_area(vertexB - vertexA, ray_int->point - vertexA) /area;
		float areaBeta = simpler_triangle_area(ray_int->point - vertexB, ray_int->point - vertexC) / area;
		float areaGamma = simpler_triangle_area(ray_int->point - vertexA, vertexC - vertexA) /area;

		float sum = areaAlpha + areaBeta + areaGamma;
		if (fabsf(1 - sum) < BIGGER_EPSILON)
		{
			if (ray_int->distance < rec.distance && ray_int->distance > 0)
			{
				rec.hit = true;
				rec.distance = ray_int->distance;
				rec.shape_id = id;
				rec.point = ray_int->point;
			}
		}
	}
	delete ray_int;
}

vector2 triangle::get_uv(vector3 point) const
{
	//computing barymetric area ratios
	float areaAlpha = simpler_triangle_area(vertexB - vertexA, point - vertexA) / area;
	float areaBeta = simpler_triangle_area(point - vertexB, point - vertexC) / area;
	float areaGamma = simpler_triangle_area(point - vertexA, vertexC - vertexA) / area;

	float u = u_top * areaBeta + areaGamma;
	float v = areaAlpha + areaGamma;

	return { u,v };
}

vector3 triangle::get_normal(vector3 point) const
{
	return normal;
}