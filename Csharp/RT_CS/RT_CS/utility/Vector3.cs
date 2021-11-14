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

        public static Vector3 operator *(Vector3 v, float f)
        {
            return new Vector3()
            {
                x = v.x * f,
                y = v.y * f,
                z = v.z * f
            };
        }

        public static Vector3 operator *(Vector3 v1, Vector3 v2)
        {
            return new Vector3()
            {
                x = v1.y * v2.z - v1.z * v2.y,
                y = v1.z * v2.x - v1.x * v2.z,
                z = v1.x * v2.y - v1.y * v2.x
            };
        }

        public static Vector3 operator *(float f, Vector3 v)
        {
            return new Vector3()
            {
                x = v.x * f,
                y = v.y * f,
                z = v.z * f
            };
        }
        public static Vector3 operator -(Vector3 v1, Vector3 v2)
        {

            return new Vector3()
            {
                x = v1.x - v2.x,
                y = v1.y - v2.y,
                z = v1.z - v2.z
            };

        }

        public static Vector3 operator +(Vector3 v1, Vector3 v2)
        {

            return new Vector3()
            {
                x = v1.x + v2.x,
                y = v1.y + v2.y,
                z = v1.z + v2.z
            };

        }
    }
    }
