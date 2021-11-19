using System;
using System.Collections.Generic;
using System.Text;
using RT_CS.sceneObjects;
using RT_CS.Cameras;
using RT_CS.utility;

namespace RT_CS.utility
{
    class Renderer
    {
        private SceneDatabase database; 
        public Renderer (SceneDatabase scd)
        {
            database = scd;
        }
        public void Render ()
        {
            float width = database.MyScene.Width;
            float height = database.MyScene.Height;
            Camera c1 = database.MyCamera;
            for (int y = 0; y<height; y++)
            {

                for (int x = 0; x<width; x++)
                {

                }
            }
        }
    }
}
