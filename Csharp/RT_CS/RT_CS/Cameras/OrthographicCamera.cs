using System;
using System.Collections.Generic;
using System.Text;
using RT_CS.utility;

namespace RT_CS.Cameras
{
    public class OrthographicCamera : Camera
    {
        public override ray Project(float px, float py)
        {
            ray myRay;
            Vector3 dir = ComputePixel(px, py);
            myRay.posit = dir;
            myRay.direct = viewDirection;
            return myRay;
        }
        public OrthographicCamera (float fl, float fp, Vector3 up, Vector3 po, Vector3 ta, float fi, float scw, float sch) :
            base (fl, fp, up, po, ta, fi, scw, sch)
        {

        }

    }
}
