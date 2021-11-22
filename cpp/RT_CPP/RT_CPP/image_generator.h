#pragma once
#include "vector3.h"
#include <string>

using namespace std;

namespace utility
{
	namespace io
	{
		class image_generator
		{
		public:
			static void write_pixels(vector3** pixels, int width, int height, string output);
		};
	}
}