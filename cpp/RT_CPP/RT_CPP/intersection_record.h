#pragma once
#include "vector3.h"
#include <cfloat>
namespace utility
{
	class intersection_record
	{
	public:
		vector3 point;
		int shape_id;
		float distance = FLT_MAX;
		bool hit;
	};
}