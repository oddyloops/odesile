using System;
using System.Collections.Generic;
using System.Text;

namespace RT_CS.utility
{
    public struct Vector3
    {
        public float x, y, z;

        public float Magnitude()
        {
            return (float)Math.Sqrt(x * x + y * y + z * z);
        }

        public Vector3 Normalize()
        {
            float magnitude = Magnitude();
            return this / magnitude;
        }

        public static Vector3 operator /(Vector3 v, float f)
        {
            return new Vector3()
            {
                x = v.x / f,
                y = v.y / f,
                z = v.z / f
            };
        }
    }
}
