#pragma once
#include "triangle.h"

using namespace utility;

namespace shapes
{
	class rectangle : public triangle
	{
	private:
		vector3 vertexD;
		vector3 vavd;
		vector3 vavb;
		float vavdMag;
		float vavbMag;

	public:
		rectangle(int id, int mid, vector3 a, vector3 b, vector3 c, vector3 d);

		void intersect(ray r, intersection_record& rec) const;

		vector2 get_uv(vector3 point) const;

	};
}