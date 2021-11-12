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
	};
}