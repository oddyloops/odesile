using RT_CS.utility;
using System;
using System.Collections.Generic;
using System.Text;

namespace RT_CS.Lights
{
    public class PointLight : Light
    {
        protected Vector3 origin;

        public PointLight(int lid, Vector3 d, Vector3 c,Vector3 o) : base(lid,d,c)
        {
            origin = o;
        }

        public override Vector3 GetDirection(Vector3 point)
        {
            return (point - origin).Normalize();
        }
    }
}
