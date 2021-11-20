#include "perspective.h"
#include "operators.h"
using namespace cameras;

perspective::perspective(float farPlane, float focalLength, float fovRadians, vector3 upDirection, vector3 target, vector3 position,
	int sceneWidth, int sceneHeight) :
	 camera(farPlane,focalLength,fovRadians,upDirection,target,position,sceneWidth,sceneHeight)
{
	
}

ray perspective::project(int pX, int pY) const
{
	ray r;
	r.position = position;
	vector3 pixelPosition = computePixelPosition(pX, pY);
	r.direction = (pixelPosition - r.position).normalize();
	return r;
}