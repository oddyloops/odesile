using System;
using System.Collections.Generic;
using System.Text;
using RT_CS.Cameras;
using RT_CS.shapes;

namespace RT_CS.sceneObjects
{
    public class SceneDatabase
    {
        public Scene MyScene { get; set; }
        public Camera MyCamera { get; set; }
        public List<Shape> MyShapes { get; set; }
    }
}
