using RT_CS.utility;
using System;
using System.Collections.Generic;
using System.Text;

namespace RT_CS.Lights
{
    public class SpotLight : PointLight
    {
        private float innerAngleCos;
        private float outerAngleCos;
        private float fallOff;

        public SpotLight(int lid, Vector3 d, Vector3 c, Vector3 o,float ia, float oa,float f) : base(lid, d, c,o)
        {
            innerAngleCos = MathF.Cos(0.5f * ia);
            outerAngleCos = MathF.Cos(0.5f * oa);
            fallOff = f;
        }


        public override Vector3 GetColor(Vector3 point)
        {
            Vector3 pointDir = GetDirection(point);
            float pointCos = Vector3.Dot(pointDir, direction);
            if(pointCos > innerAngleCos)
            {
                //within full illumination
                return color;
            }
            else if(pointCos < outerAngleCos)
            {
                //no illumination
                return new Vector3() { x = 0, y = 0, z = 0 };
            }
            else
            {
                //compute fall-off
                float fraction = MathF.Pow((pointCos - outerAngleCos) / (innerAngleCos - outerAngleCos), fallOff);
                return fraction * color;
            }
        }
    }
}
