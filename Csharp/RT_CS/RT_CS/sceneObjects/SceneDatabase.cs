using System;
using System.Collections.Generic;
using System.Text;
using RT_CS.Cameras;
using RT_CS.shapes;
using RT_CS.Lights;
using RT_CS.Materials;

namespace RT_CS.sceneObjects
{
    public class SceneDatabase
    {
        public Scene MyScene { get; set; }
        public Camera MyCamera { get; set; }
        public List<Shape> MyShapes { get; set; }
        public List<Light> MyLights { get; set; }
        public List<Material> MyMaterials { get; set; }

        public Shape GetShapeById(int id)
        { 
            foreach (Shape shape in MyShapes)
            {
                if(id == shape.GetId())
                    return shape;
            }
            return null;
        }

        public Material GetMaterialById (int id)
        { 
            foreach (Material material in MyMaterials)
            {
                if (id == material.GetId())
                    return material;
            }
            return null;
        }
    }
}
