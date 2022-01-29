#include "sphere.h"
#include "ray.h"
#include "operators.h"
#include <math.h>
# define M_PI           3.14159265358979323846 
#include <cfloat>
using namespace shapes;

sphere ::sphere (int id,int mid, vector3 c, float r) : shape(id,mid),
center(c), radius(r)
{

}

void sphere:: intersect(ray r, intersection_record& rec)  const
{
	if (id == rec.except_id)
	{
		return;
	}
	vector3 sub_1 = r.position - center;
	float sub_2 = vector3::dot(sub_1, r.direction);
	float grad = (sub_2 * sub_2) - (sub_1.magnitude_sq() - (radius * radius));
	float d = -sub_2;
	float dist = 0;
	if (fabsf(grad) < FLT_EPSILON)
	{
		dist = d;
	}

	else if (grad > FLT_EPSILON)
	{
		grad = sqrtf(grad);
		dist = fminf(d + grad, d - grad);
	}
	else
	{
		return;
	}
	
	if (dist > 0 && dist < rec.distance)
	{
		rec.hit = true;
		rec.distance = dist;
		rec.shape_id = id;
		rec.point = r.position + r.direction * dist;
	}
}

vector3 sphere::get_normal(vector3 point) const
{
	return (point - center).normalize();
}

vector2 sphere::get_uv(vector3 point) const
{
	vector3 normal = get_normal(point);
	float u = (atan2f(normal.x, normal.z) / (2 * M_PI)) + 0.5;
	float v = 0.5 - (asinf(normal.y) / M_PI);
	return { u,v };
}