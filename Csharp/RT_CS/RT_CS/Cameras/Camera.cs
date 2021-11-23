using RT_CS.utility;
using System;
using System.Collections.Generic;
using System.Text;

namespace RT_CS.Cameras
{
    public abstract class Camera
    {
        protected float focalLength;
        protected float farPlane;
        protected Vector3 upDirection;
        protected Vector3 position;
        protected Vector3 target;
        protected float fieldOfView;
        protected Vector3 viewDirection;
        protected Vector3 sideDirection;
        protected Vector3 cameraUp;
        protected Vector3 c1, c2, c3, c4;
        protected float frameWidth;
        protected float frameHeight;
        protected float pixelWidth;
        protected float pixelHeight;

        public abstract Ray Project(int px, int py);

        public Vector3 ComputePixel(int px, int py)
        {
            float hor = (px + 0.5f) * pixelWidth;
            float ver = (py + 0.5f) * pixelHeight;
            Vector3 position1 = c1 - sideDirection * hor;
            Vector3 position2 = position1 - cameraUp * ver;
            return position2;
        }
        public Camera (float fl, float fp, Vector3 up, Vector3 po, Vector3 ta, float fi, int scw, int sch)
        {
            focalLength = fl;
            farPlane = fp;
            upDirection = up;
            position = po;
            target = ta;
            fieldOfView = fi;


            viewDirection = target - position;
            viewDirection = viewDirection.Normalize();
            Vector3 centre = position + (focalLength * viewDirection);
            sideDirection = upDirection * viewDirection;
            cameraUp = viewDirection * sideDirection;
            float halfHeight = focalLength * (float)Math.Tan(0.5 * fieldOfView);
            float aspectRatio = (float)scw / sch;
            float halfWidth = halfHeight * aspectRatio;
            Vector3 top = centre + (halfHeight * cameraUp);
            Vector3 bottom = centre - (halfHeight * cameraUp);
            c1 = top + (halfWidth * sideDirection);
            c2 = top - (halfWidth * sideDirection);
            c3 = bottom - (halfWidth * sideDirection);
            c4 = bottom + (halfWidth * sideDirection);
            frameHeight = halfHeight * 2;
            frameWidth = halfWidth * 2;
            pixelHeight = frameHeight / sch;
            pixelWidth = frameWidth / scw;
        }
     
        
    }
}
