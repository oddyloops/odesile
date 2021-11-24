#include "camera.h"
#include "operators.h"

#include <math.h>

using namespace cameras;

camera::camera(float farPlane, float focalLength, float fovRadians, vector3 upDirection, vector3 target, vector3 position,
	int sceneWidth, int sceneHeight)
	: farPlane(farPlane), focalLength (focalLength),  fovRadians(fovRadians), upDirection (upDirection), target (target), position (position)
{
	viewDirection = target - position;
	viewDirection = viewDirection.normalize();
	
	vector3 center = position + focalLength * viewDirection;
	sideDirection = (upDirection * viewDirection).normalize();
	cameraUp = (viewDirection * sideDirection).normalize();

	float halfHeight = focalLength * tanf(0.5 * fovRadians);
	float aspectRatio = (float)sceneWidth / sceneHeight;
	float halfWidth = aspectRatio * halfHeight;
	vector3 p = center + halfHeight * cameraUp;
	vector3 q = center - halfHeight * cameraUp;
	c1 = p + halfWidth * sideDirection;
	c2 = p - halfWidth * sideDirection;
	c3 = q - halfWidth * sideDirection;
	c4 = q + halfWidth * sideDirection;
	
	frameWidth = 2 * halfWidth;
	frameHeight = 2 * halfHeight;
	pixelWidth = frameWidth / sceneWidth;
	pixelHeight = frameHeight / sceneHeight;

}


vector3 camera::computePixelPosition(int pX, int pY) const
{
	vector3 hor = c1 - ((pX + 0.5) * pixelWidth * sideDirection);
	return hor - ((pY + 0.5) * pixelHeight * upDirection);
}