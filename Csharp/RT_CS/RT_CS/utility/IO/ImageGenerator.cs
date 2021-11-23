using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.Text;

namespace RT_CS.utility.IO
{
    public class ImageGenerator
    {
        public static void WritePixels(Vector3[,] pixels, int width, int height, string output)
        {
            using Bitmap image = new Bitmap(width, height);
            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    image.SetPixel(x, y, VecColor(pixels[y, x]));
                }
            }
            image.Save(output, ImageFormat.Bmp);
        }

        private static Color VecColor(Vector3 pixel)
        {
            return Color.FromArgb(
                (int)(255 * pixel.x), (int)(255 * pixel.y), (int)(255 * pixel.z)
                );
        }
    }
}
