using RT_CS.utility;
using RT_CS.Cameras;
using System;
using System.Collections.Generic;
using System.Text;

namespace RT_CS.shapes
{

    public class Rectangle : Triangle
    {
        private Vector3 vertexD,vdva,vdvc;

        public Rectangle(int id, int mid, Vector3 v1, Vector3 v2, Vector3 v3, Vector3 v4) : base(id, mid, v1, v2, v3)
        {
            vertexD = v4;
          
            vdva = v4 - v1;
            vdvc = v4 - v3;
            float vdvaMag = vdva.Magnitude();
            float vdvcMag = vdvc.Magnitude();
            area = vdvaMag * vdvcMag;
            normal = ((v3 - v4) * (v1 - v4)).Normalize();
            vdva /= vdvaMag;
            vdvc/=vdvcMag;
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
                float alpha = SimplerTriangleArea(vertexA - inter.Point,  vertexA - vertexD)/area;
                float beta = SimplerTriangleArea(vertexB - inter.Point,  vertexB - vertexA) /area;
                float gamma = SimplerTriangleArea( vertexC - inter.Point, vertexC - vertexB)/area;
                float phi = SimplerTriangleArea(vertexD - inter.Point, vertexD - vertexC)/area;
                float sum = alpha + beta + gamma + phi;
               
                if (Math.Abs(1 - sum) < BIGGER_EPSILON)
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
