#include "texture.h"


using namespace utility;

texture::texture(vector3** pixels, int width, int height) : pixels(pixels), width(width), height(height)
{

}

texture::~texture()
{
	for (int i = 0; i < height; i++)
	{
		delete pixels[i];
	}
	delete pixels;
}

vector3 texture::get_pixel(vector2 uv)
{
	int x = (int)fmaxf(0, roundf(uv.x * width) - 1);
	int y = (int)fmaxf(0, roundf(uv.y * height) - 1);
	return pixels[y][x];
}