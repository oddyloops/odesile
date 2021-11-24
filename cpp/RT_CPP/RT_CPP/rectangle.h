#pragma once
#include "triangle.h"

using namespace utility;

namespace shapes
{
	class rectangle : public triangle
	{
	private:
		vector3 vertexD;
		vector3 vcvb;
		vector3 vdvc;

	public:
		rectangle(int id, vector3 a, vector3 b, vector3 c, vector3 d);

		void intersect(ray r, intersection_record& rec);

	};
}