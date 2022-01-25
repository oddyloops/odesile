#pragma once
#include "vector3.h"
#include "vector2.h"
#include <math.h>


namespace utility
{
	class texture
	{
	private:
		vector3** pixels;
		int width, height;

	public:
		texture(vector3** pixels, int width, int height);
		vector3 get_pixel(vector2 uv);
	};
}