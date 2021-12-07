#include "rectangle.h"
#include "operators.h"
using namespace shapes;

rectangle::rectangle(int id, vector3 a, vector3 b, vector3 c, vector3 d)
	: triangle(id,a,b,c), vertexD(d)
{
	vcvb = (vertexC - vertexB).normalize();
	vdvc = (vertexD - vertexC).normalize();
}


void rectangle::intersect(ray r, intersection_record& rec) const
{
	intersection_record* ray_rec = ray_plane_intersection(r);
	if (ray_rec->hit)
	{
		vector3 pb = (ray_rec->point - vertexB).normalize();
		float cos = vector3::dot(pb, vcvb);
		float sin = (pb * vcvb).magnitude();
		if (cos >= 0 && sin >= 0)
		{
			vector3 pd = (ray_rec->point - vertexD).normalize();
			cos = vector3::dot(pd, vdvc);
			sin = (pd * vdvc).magnitude();
			if (cos >= 0  && sin >= 0)
			{
				if (ray_rec->distance < rec.distance)
				{
					rec.hit = true;
					rec.distance = ray_rec->distance;
					rec.shape_id = id;
					rec.point = ray_rec->point;
				}
			}
		}
	}
}
