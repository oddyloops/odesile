#pragma once
#include "vector3.h"

using namespace utility;

namespace cameras
{
	struct ray
	{
	public:
		vector3 position;
		vector3 direction;
	};
}