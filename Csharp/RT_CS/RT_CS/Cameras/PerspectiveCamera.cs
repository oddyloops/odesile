using System;
using System.Collections.Generic;
using System.Text;
using RT_CS.utility;

namespace RT_CS.Cameras
{
    public class PerspectiveCamera : Camera
    {
        public override Ray Project(float px, float py)
        {
            Ray myRay;
            Vector3 dir = ComputePixel(px, py);
            myRay.posit = position;
            myRay.direct = (dir - position).Normalize();
            return myRay;

        }
        public PerspectiveCamera (float fl, float fp, Vector3 up, Vector3 po, Vector3 ta, float fi, float scw, float sch) : 
            base (fl,fp,up,po,ta,fi,scw,sch)
        {

        }
    }
}
