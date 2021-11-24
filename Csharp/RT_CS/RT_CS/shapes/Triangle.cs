using RT_CS.Cameras;
using RT_CS.utility;
using System;
using System.Collections.Generic;
using System.Text;

namespace RT_CS.shapes
{

    public class Triangle : Shape
    {
        protected Vector3 vertexA, vertexB, vertexC, normal;
        protected float D;

        public Triangle(int id, Vector3 v1, Vector3 v2, Vector3 v3)  :base(id)
        {
            vertexA = v1;
            vertexB = v2;
            vertexC = v3;
            normal = ((v3 - v1) * (v2 - v1)).Normalize();
            D = v1.Magnitude();
        }
        public IntersectionRecord RayPlaneIntersection(Ray r)
        {
            IntersectionRecord inter = new IntersectionRecord();
            float nordir = Vector3.Dot(r.direct, normal);
            if (Math.Abs(nordir) < float.Epsilon)
            {
                return inter;
            }
            else
            {
                float d = (-(Vector3.Dot(r.posit, normal) + D))/nordir;
                if (d > 0)
                {
                    inter.Distance = d;
                    inter.Hit = true;
                    inter.Point = r.posit + d * r.direct;
                }
                return inter;
            }
        }

        public override void Intersect(Ray r, IntersectionRecord intersection)
        {
            throw new NotImplementedException();
        }
    }


}
