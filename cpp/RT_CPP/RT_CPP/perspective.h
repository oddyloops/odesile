#pragma once
#include "camera.h"
namespace cameras
{
	class perspective : public camera
	{
	public:
		perspective(float farPlane, float focalLength, float fovRadians, vector3 upDirection, vector3 target, vector3 position,
			int sceneWidth, int sceneHeight);

		ray project(int pX, int pY) const;

	};
}
