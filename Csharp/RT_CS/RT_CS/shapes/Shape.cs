using RT_CS.Cameras;
using RT_CS.utility;
using System;
using System.Collections.Generic;
using System.Text;

namespace RT_CS.shapes
{
    public abstract class Shape
    {
        protected int sid;

        public Shape(int id)
        {
            sid = id;
        }

        public abstract void Intersect(Ray r,IntersectionRecord intersection);
    }

}
