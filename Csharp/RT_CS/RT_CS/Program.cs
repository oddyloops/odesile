using System;

namespace RT_CS
{
    namespace utility
    {
        struct Vector3
        {
            public float x, y, z;
        }

        namespace SceneObjects
        {
            class Scene
            {
                private float length, width;
            }
        }

        namespace shapes
        {
            class Shape
            { }

            class Sphere : Shape
            {
                private Vector3 centre;
            }

            class Triangle : Shape 
            {
                protected Vector3 VertexA, VertexB, VertexC;
            }
            class Rectangle : Shape
            {
                private Vector3 VertexD;
            }
        }
    }

   
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
        }
    }
}
