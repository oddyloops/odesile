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

        public override Vector3 GetNormal(Vector3 point)
        {
            return (point - centre).Normalize();
        }

        public Sphere(int id,int mid, Vector3 c, float r) : base(id, mid)
        {
            centre = c;
            radius = r;
        }


        public override void Intersect(Ray r, IntersectionRecord record)
        {
            if (record.ExceptId == sid)
            {
                return;
            }
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

           
            if( dist > 0 && dist < record.Distance)
            {
                record.Distance =dist;
                record.Hit = true;
                record.Point = r.posit + dist * r.direct;
                record.ShapeId = sid;
            }
            
        }

        public override Vector2 GetUV(Vector3 pt)
        {
            Vector3 normal = GetNormal(pt);
            float u = MathF.Atan2(normal.x, normal.z) / (2 * MathF.PI) + 0.5F;
            float v = normal.y * 0.5F + 0.5F;
            return new Vector2() {  x = u, y = v };
        }
    }

}
