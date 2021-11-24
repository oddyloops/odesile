using RT_CS.utility;
using RT_CS.Cameras;
using System;
using System.Collections.Generic;
using System.Text;

namespace RT_CS.shapes
{

    public class Rectangle : Triangle
    {
        private Vector3 vertexD,vcvb,vdvc;

        public Rectangle(int id, Vector3 v1, Vector3 v2, Vector3 v3, Vector3 v4) : base(id, v1, v2, v3)
        {
            vertexD = v4;
            vcvb = (v3 - v2).Normalize();
            vdvc = (v4 - v3).Normalize();
        }

        public override void Intersect(Ray r, IntersectionRecord intersection)
        {
            IntersectionRecord inter = RayPlaneIntersection(r);
            Vector3 pb = (inter.Point - vertexB).Normalize();
            float cos = Vector3.Dot(pb, vcvb);
            float sin = (pb * vcvb).Magnitude();
            if (cos >= 0 && sin >= 0)
            {
                Vector3 pd = (inter.Point - vertexD).Normalize();
                cos = Vector3.Dot(pd, vdvc);
                sin = (pd * vdvc).Magnitude();

                if (cos >= 0 && sin >= 0 && inter.Distance < intersection.Distance)
                {
                    intersection.Distance = inter.Distance;
                    intersection.Hit = true;
                    intersection.Point = inter.Point;
                    intersection.ShapeId = sid;
                }
            }
        }
    }


}
