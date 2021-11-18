#include "perspective.h"
#include "operators.h"
using namespace cameras;

perspective::perspective(float farPlane, float focalLength, float fovRadians, vector3 upDirection, vector3 target, vector3 position,
	float sceneWidth, float sceneHeight) :
	 camera(farPlane,focalLength,fovRadians,upDirection,target,position,sceneWidth,sceneHeight)
{
	
}

ray perspective::project(float pX, float pY)
{
	ray r;
	r.position = position;
	vector3 pixelPosition = computePixelPosition(pX, pY);
	r.direction = (pixelPosition - r.position).normalize();
	return r;
}