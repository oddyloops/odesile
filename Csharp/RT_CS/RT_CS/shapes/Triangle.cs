using RT_CS.Cameras;
using RT_CS.utility;
using System;
using System.Collections.Generic;
using System.Text;

namespace RT_CS.shapes
{

    public class Triangle : Shape
    {
        protected Vector3 vertexA, vertexB, vertexC;

        public Triangle(int id)  :base(id)
        {

        }

        public override void Intersect(Ray r, IntersectionRecord intersection)
        {
            throw new NotImplementedException();
        }
    }


}
