#pragma once
#include "shape.h"
#include "vector3.h"

using namespace utility;

namespace shapes
{
	class sphere : public shape
	{
	private:
		vector3 center;
		float radius;

	public :
		sphere(int id,int mid, vector3 c, float r);
		void intersect(ray r, intersection_record& rec) const;
		vector3 get_normal(vector3 point) const;
	};

	
}