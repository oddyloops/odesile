#include "orthographic.h"
using namespace cameras;

orthographic::orthographic(float farPlane, float focalLength, float fovRadians, vector3 upDirection, vector3 target, vector3 position,
	float sceneWidth, float sceneHeight) :
	camera(farPlane, focalLength, fovRadians, upDirection, target, position, sceneWidth, sceneHeight)
{

}

ray orthographic::project(int pX, int pY) const
{
	ray r;
	r.position = computePixelPosition(pX, pY);
	r.direction = viewDirection;
	return r;
}