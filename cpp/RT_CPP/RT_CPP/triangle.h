#pragma once
#include "shape.h"
#include "vector3.h"
using namespace utility;
namespace shapes
{
	class triangle : public shape
	{
	protected:
		vector3 vertexA;
		vector3 vertexB;
		vector3 vertexC;
	};
}