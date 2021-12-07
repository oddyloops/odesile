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
        private Vector3 ab,ac,bc;
        private float area;
        private static float TriangleArea (Vector3 ab, Vector3 ac, Vector3 vA, Vector3 vB)
        {
            Vector3 normAb = ab.Normalize();
            Vector3 normAc = ac.Normalize();
            float cosTheta = Vector3.Dot(normAb, normAc);
            float hypotenus = ab.Magnitude();
            float adjacent = hypotenus * cosTheta;
            Vector3 adjend = vA + (adjacent * normAc);
            float height = (vB - adjend).Magnitude();
            return 0.5f *height * ac.Magnitude();
        }

        public Triangle(int id, Vector3 v1, Vector3 v2, Vector3 v3)  :base(id)
        {
            vertexA = v1;
            vertexB = v2;
            vertexC = v3;
            ab = vertexB - vertexA;
            ac = vertexC - vertexA;
            bc = vertexC - vertexA;
            normal = ((v3 - v1) * (v2 - v1)).Normalize();
            D = v1.Magnitude();
            area = TriangleArea(ab, ac, vertexA, vertexB);
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
            IntersectionRecord inter = RayPlaneIntersection(r);
            if (inter.Hit)
            {
                float areaAlpha = TriangleArea(inter.Point - vertexB, vertexA - vertexB, vertexB, inter.Point)/area;
                float areaBeta = TriangleArea(inter.Point - vertexC, vertexB - vertexC, vertexC, inter.Point)/area;
                float areaGamma = TriangleArea(inter.Point - vertexA, vertexC - vertexA, vertexA, inter.Point)/area;
                float sum = areaAlpha + areaBeta + areaGamma;

                if(Math.Abs(1-sum) < float.Epsilon)
                {
                    if (inter.Distance < intersection.Distance)
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


}
