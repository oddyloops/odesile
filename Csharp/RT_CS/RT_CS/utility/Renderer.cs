using System;
using System.Collections.Generic;
using System.Text;
using RT_CS.sceneObjects;
using RT_CS.Cameras;
using RT_CS.utility;
using RT_CS.shapes;
using RT_CS.utility.IO;

namespace RT_CS.utility
{
    class Renderer
    {
        private SceneDatabase database; 
        public Renderer (SceneDatabase scd)
        {
            database = scd;
        }
        private IntersectionRecord RunIntersection (Camera cam, List<Shape> shapes, int pX, int pY)
        {
            IntersectionRecord inter = new IntersectionRecord();
            Ray myRay = cam.Project(pX, pY);
            foreach (Shape s in shapes)
            {
                s.Intersect(myRay, inter);
            }
            return inter;
        }
        public Vector3[,] Render ()
        {
            int width = database.MyScene.Width;
            int height = database.MyScene.Height;
            Camera c1 = database.MyCamera;
            List<Shape> myShapes = database.MyShapes;
            Vector3[,] image = new Vector3[height,width];
            for (int y = 0; y<height; y++)
            {

                for (int x = 0; x<width; x++)
                {
                    IntersectionRecord record = RunIntersection(c1, myShapes, x, y);
                    Vector3 pxcolour = new Vector3();
                    if (record.Hit)
                    {
                        pxcolour.x = 1;
                        pxcolour.y = 1;
                        pxcolour.z = 1;
                    }
                    else
                    {
                        pxcolour = database.MyScene.Background;
                    }
                    image[y, x] = pxcolour;
                }
            }
            return image;
        }
    }
}
