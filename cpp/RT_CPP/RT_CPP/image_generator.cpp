#include "image_generator.h"
#include "io/EasyBMP.cpp"

using namespace utility::io;

void image_generator::write_pixels(vector3** pixels, int width, int height, string output)
{
	BMP input;
	input.SetSize(width, height);
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			
			input(x, y)->Alpha = 255;
			input(x, y)->Red = static_cast<unsigned char>(static_cast<int>(pixels[y][x].x * 255));
			input(x, y)->Green = static_cast<unsigned char>(static_cast<int>(pixels[y][x].y * 255));
			input(x, y)->Blue = static_cast<unsigned char>(static_cast<int>(pixels[y][x].z * 255));

		}
	}
	input.WriteToFile(output.c_str());
}