#pragma once
#include "shape.h"
#include "vector3.h"
using namespace utility;
namespace shapes
{
	class triangle : public shape
	{

	private:
		vector3 ab;
		vector3 bc;
		vector3 ac;


		
	protected:
		vector3 vertexA;
		vector3 vertexB;
		vector3 vertexC;
		vector3 normal;
		vector3 d;
		float area;
		const float BIGGER_EPSILON = 0.00001f;
		static float simpler_triangle_area(vector3 ab, vector3 ac);
	public:
		triangle(int id,int mid, vector3 a, vector3 b, vector3 c);
		intersection_record* ray_plane_intersection(ray r) const;
		vector3 get_normal(vector3 point) const;
		void intersect(ray r, intersection_record& rec) const;
	};
}