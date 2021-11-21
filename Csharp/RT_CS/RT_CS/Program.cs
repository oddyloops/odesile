using RT_CS.sceneObjects;
using RT_CS.utility;
using RT_CS.utility.IO;
using System;
using System.IO;

namespace RT_CS
{

   
    class Program
    {
        static void Main(string[] args)
        {
            string filePath = Path.Join(Directory.GetParent(Environment.CurrentDirectory).Parent.Parent.FullName, args[0]);
            Console.WriteLine("Loading scene from" + filePath);
            SceneDatabase db =DatabaseLoader.Load(filePath);
            Renderer renderer = new Renderer(db);
            Vector3[,] image = renderer.Render();
            ImageGenerator.WritePixels(image, db.MyScene.Width, db.MyScene.Height, "img.bmp");
            Console.WriteLine("Done");
            Console.Read();
        }
    }
}
