#pragma once
#include "triangle.h"

using namespace utility;

namespace shapes
{
	class rectangle : public triangle
	{
	private:
		vector3 vertexD;
	};
}