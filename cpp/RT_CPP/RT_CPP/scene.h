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
		vector3 ambientLight;

	public:
		int get_height() const;

		int get_width() const;

		vector3 get_ambient_light() const;

		vector3 get_background() const;

		void set_width(int w);

		void set_height(int h);

		void set_ambient_light(vector3 amb);

		void set_background(vector3 bg);
	};
}