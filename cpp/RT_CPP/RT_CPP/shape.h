#pragma once
#include "intersection_record.h"
#include "ray.h"
using namespace cameras;
namespace shapes

{
	class shape
	{

	protected:
		int id;

	public:
		shape(int ids)
		{
			id = ids;
		}

		virtual void intersect(ray r, intersection_record& rec) = 0;
	};
}