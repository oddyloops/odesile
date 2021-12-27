#include <math.h>
#include "rectangle.h"
#include "operators.h"
using namespace shapes;

rectangle::rectangle(int id,int mid, vector3 a, vector3 b, vector3 c, vector3 d)
	: triangle(id,mid,a,b,c), vertexD(d)
{
	vcvb = vertexC - vertexB;
	vdvc = vertexD - vertexC;
	float vcvbMag = vcvb.magnitude();
	float vdvcMag = vdvc.magnitude();
	area = vcvbMag * vdvcMag;
	vcvb = vcvb / vcvbMag;
	vdvc = vdvc / vdvcMag;
}


void rectangle::intersect(ray r, intersection_record& rec) const
{
    if (id == rec.except_id)
    {
        return;
    }
	intersection_record* ray_rec = ray_plane_intersection(r);
	if (ray_rec->hit)
	{
        float alpha = simpler_triangle_area(vertexD - vertexA, vertexD - ray_rec->point) / area;
        float beta = simpler_triangle_area(ray_rec->point - vertexA, ray_rec->point - vertexB) / area;
        float gamma = simpler_triangle_area(ray_rec->point - vertexB, ray_rec->point - vertexC) / area;
        float phi = simpler_triangle_area(vertexD - ray_rec->point, vertexD - vertexC) / area;
        float sum = alpha + beta + gamma + phi;

        if (fabsf(1 - sum) < BIGGER_EPSILON)
        {
            if (ray_rec->distance < rec.distance && ray_rec->distance > 0)
            {
                rec.distance = ray_rec->distance;
                rec.hit = true;
                rec.point = ray_rec->point;
                rec.shape_id = id;
            }
        }
	}
    delete ray_rec;
}
