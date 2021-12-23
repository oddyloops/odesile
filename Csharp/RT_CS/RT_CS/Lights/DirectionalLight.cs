using RT_CS.utility;
using System;
using System.Collections.Generic;
using System.Text;

namespace RT_CS.Lights
{
    public class DirectionalLight : Light
    {
        public DirectionalLight(int lid, Vector3 d, Vector3 c) : base(lid,d,c)
        {

        }

        public override Vector3 GetDirection(Vector3 point)
        {
            return direction;
        }

        public override float LightPointDistance(Vector3 point)
        {
            return float.PositiveInfinity;
        }
    }
}
