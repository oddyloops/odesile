using RT_CS.Cameras;
using RT_CS.utility;
using System;
using System.Collections.Generic;
using System.Text;

namespace RT_CS.shapes
{

    public class Sphere : Shape
    {
        private Vector3 centre;
        private float radius;

        public Sphere(int id,Vector3 c, float r) : base(id)
        {
            centre = c;
            radius = r;
        }


        public override void Intersect(Ray r, IntersectionRecord record)
        {
            IntersectionRecord intersect = new IntersectionRecord();

            Vector3 oc = r.posit - centre;
            float uOc = Vector3.Dot(r.direct, oc);
            float root = uOc * uOc - (oc.MagnitudeSq() - radius * radius);
            float d = -uOc;
            float dist = 0;
            if (Math.Abs(root) < float.Epsilon )
            {
                dist = d;
            }
            else if (root > float.Epsilon)
            {
                root = (float)Math.Sqrt(root);
                dist = Math.Min(d + root, d - root);
            }
            else
            {//< 0 means no intersection
                return;
            }

           
            if( dist > 0 && dist < intersect.Distance)
            {
                intersect.Distance =dist;
                intersect.Hit = true;
                intersect.Point = r.posit + dist * r.direct;
                intersect.ShapeId = sid;
            }
            
        }
    }

}
