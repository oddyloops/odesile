#pragma once
#include "ray.h"
#include "vector3.h"
using namespace utility;
namespace cameras
{
	class camera
	{
	protected: 
		float farPlane, focalLength;
		vector3 upDirection;
		vector3 target;
		vector3 position;
		float fovRadians;

		vector3 viewDirection;
		vector3 sideDirection;
		vector3 cameraUp;

		vector3 c1;
		vector3 c2;
		vector3 c3;
		vector3 c4;

		float frameWidth;
		float frameHeight;
		float pixelWidth;
		float pixelHeight;


	public:
		camera(float farPlane, float focalLength, float fovRadians, vector3 upDirection, vector3 target, vector3 position,
			int sceneWidth, int sceneHeight);

		vector3 get_view_direction() const;

		vector3 computePixelPosition(int pX, int pY) const;

		virtual ray project(int pX, int pY) const = 0;
		

	};
}