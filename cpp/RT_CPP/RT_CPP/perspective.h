#pragma once
#include "camera.h"
namespace cameras
{
	class perspective : public camera
	{
	public:
		perspective(float farPlane, float focalLength, float fovRadians, vector3 upDirection, vector3 target, vector3 position,
			float sceneWidth, float sceneHeight);

		ray project(float pX, float pY);

	};
}
