using System;
using System.Collections.Generic;
using System.Text;
using RT_CS.utility;

namespace RT_CS.Cameras
{
    public class OrthographicCamera : Camera
    {
        public override Ray Project(int px, int py)
        {
            Ray myRay;
            Vector3 dir = ComputePixel(px, py);
            myRay.posit = dir;
            myRay.direct = viewDirection;
            return myRay;
        }
        public OrthographicCamera (float fl, float fp, Vector3 up, Vector3 po, Vector3 ta, float fi, int scw, int sch) :
            base (fl, fp, up, po, ta, fi, scw, sch)
        {

        }

    }
}
