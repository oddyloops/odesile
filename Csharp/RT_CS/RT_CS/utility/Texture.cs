using System;
using System.Collections.Generic;
using System.Text;

namespace RT_CS.utility
{
    public class Texture 
    {
        private Vector3[,] pixels;
        private int width, height;

        public Texture(Vector3[,] pxs, int w, int h)
        {
            pixels = pxs;
            width = w;
            height = h;
        }

        public Vector3 GetPixel(Vector2 uv)
        {
            int x = (int)Math.Max(0, Math.Round(uv.x * width) - 1);
            int y = (int)Math.Max(0, Math.Round(uv.y * height) - 1);
            return pixels[y,x];

        }
    }
}
