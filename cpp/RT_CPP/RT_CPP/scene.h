#pragma once
#include "vector3.h"
using namespace utility;
namespace scene_objects
{
	class scene
	{
	private:
		int height;
		int width;
		vector3 background;

	public:
		int get_height();

		int get_width();

		vector3 get_background();

		void set_width(int w);

		void set_height(int h);

		void set_background(vector3 bg);
	};
}