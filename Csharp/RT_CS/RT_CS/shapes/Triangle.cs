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
        protected Vector3 D;
        private Vector3 ab,ac,bc;
        protected float area;
        private float uTop;

        protected const float BIGGER_EPSILON = 0.000001f;


        protected static float SimplerTriangleArea(Vector3 ab,Vector3 ac)
        {
            return (ab * ac).Magnitude() * 0.5f;
        }

        public Triangle(int id, int mid, Vector3 v1, Vector3 v2, Vector3 v3)  :base(id, mid)
        {
            vertexA = v1;
            vertexB = v2;
            vertexC = v3;
            ab = vertexB - vertexA;
            ac = vertexC - vertexA;
            bc = vertexC - vertexA;
            normal = ((v3 - v1) * (v2 - v1)).Normalize();
            D = v1;
            area = SimplerTriangleArea(ab,ac);
            float acMag = ac.Magnitude();
            uTop = Vector3.Dot(ab, ac / acMag) / acMag;
        }
        public override Vector3 GetNormal(Vector3 point)
        {
            return normal;
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
                float d = Vector3.Dot((D - r.posit),normal)/nordir;
                if (d > 0)
                {
                    inter.Distance = d;
                    inter.Hit = true;
                    inter.Point = r.posit + d * r.direct;
                }
                return inter;
            }
        }

        public override Vector2 GetUV(Vector3 pt)
        {
            float areaAlpha = SimplerTriangleArea(vertexB - vertexA, pt - vertexA) / area;
            float areaBeta = SimplerTriangleArea(pt - vertexB, pt - vertexC) / area;
            float areaGamma = SimplerTriangleArea(pt - vertexA, vertexC - vertexA) / area;

            return new Vector2 { x = (uTop * areaBeta) + areaGamma, y = areaAlpha + areaGamma };
        }

        public override void Intersect(Ray r, IntersectionRecord intersection)
        {
            if (intersection.ExceptId == sid)
            {
                return;
            }
            IntersectionRecord inter = RayPlaneIntersection(r);
            if (inter.Hit)
            {
                float areaAlpha = SimplerTriangleArea(vertexB - vertexA, inter.Point - vertexA) / area;
                float areaBeta = SimplerTriangleArea(inter.Point - vertexB, inter.Point - vertexC) / area;
                float areaGamma = SimplerTriangleArea(inter.Point - vertexA, vertexC - vertexA) / area;
                float sum = areaAlpha + areaBeta + areaGamma;


                if(Math.Abs(1-sum) < BIGGER_EPSILON)
                {
                    if (inter.Distance < intersection.Distance && inter.Distance > 0)
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
