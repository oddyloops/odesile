#pragma once

#include "vector3.h"
using namespace utility;
namespace cameras
{
	class camera
	{
	protected: float farPlane, focalLength;
			 vector3 upDirection;
			 vector3 target;
			 vector3 position;
	};
}