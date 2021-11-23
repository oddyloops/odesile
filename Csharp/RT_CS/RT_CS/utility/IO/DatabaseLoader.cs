﻿using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using RT_CS.Cameras;
using RT_CS.sceneObjects;
using RT_CS.shapes;
using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace RT_CS.utility.IO
{
    public class DatabaseLoader
    {
        public static SceneDatabase Load(string filePath)
        {
            JsonSerializer serializer = new JsonSerializer();
            using StreamReader file = File.OpenText(filePath);
            JObject dbDict = (JObject)
                serializer.Deserialize(file, typeof(JObject));

            SceneDatabase db = new SceneDatabase();
            JObject temp = (JObject)dbDict["Scene"];
            LoadScene(temp, db);
            temp = (JObject)dbDict["Camera"];
            LoadCamera(temp, db);
            db.MyShapes = new List<Shape>();
            JObject shapes = (JObject)dbDict["Shapes"];
            JArray shapesArr = (JArray)shapes["Spheres"];
            LoadSpheres(shapesArr, db);
            return db;
        }

        private static Vector3 ParseVector3(string vectorStr)
        {
            string[] vectorArr = vectorStr.Split(',');
            Vector3 vector = new Vector3()
            {
                x = Convert.ToSingle(vectorArr[0]),
                y = Convert.ToSingle(vectorArr[1]),
                z = Convert.ToSingle(vectorArr[2])
            };
            return vector;
        }

        private static void LoadScene(JObject sceneDict, SceneDatabase db)
        {
            Scene scene = new Scene()
            {
                Height = (int)sceneDict["height"],
                Width = (int)sceneDict["width"],
                Background = ParseVector3((string)sceneDict["background"])
            };
            db.MyScene = scene;
        }

        private static void LoadCamera(JObject cameraDict, SceneDatabase db)
        {
            bool isOrtho =(bool)cameraDict["isOrthographic"];
            Camera camera;
            if (isOrtho)
            {
                camera = new OrthographicCamera((float)cameraDict["focalLength"],
               (float)cameraDict["farPlane"],
               ParseVector3((string)cameraDict["upDirection"]),
               ParseVector3((string)cameraDict["position"]),
               ParseVector3((string)cameraDict["target"]),
               (float)cameraDict["fieldOfView"],
               db.MyScene.Width,
               db.MyScene.Height);
            }
            else
            {
                camera = new PerspectiveCamera((float)cameraDict["focalLength"],
               (float)cameraDict["farPlane"],
               ParseVector3((string)cameraDict["upDirection"]),
               ParseVector3((string)cameraDict["position"]),
               ParseVector3((string)cameraDict["target"]),
               (float)cameraDict["fieldOfView"],
               db.MyScene.Width,
               db.MyScene.Height);
            }
            db.MyCamera = camera;

        }

        private static void LoadSpheres(JArray spheres,SceneDatabase db)
        {
            foreach(var sphere in spheres)
            {
                LoadSphere((JObject)sphere, db);
            }
        }

        private static void LoadSphere(JObject sphereDict, SceneDatabase db)
        {
            Sphere sphere = new Sphere((int)sphereDict["id"],
                ParseVector3((string)sphereDict["center"]),
                (float)sphereDict["radius"]);
            db.MyShapes.Add(sphere);
        }
    }
}