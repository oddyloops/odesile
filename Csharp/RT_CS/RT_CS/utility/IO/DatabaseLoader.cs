using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using RT_CS.Cameras;
using RT_CS.Lights;
using RT_CS.Materials;
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
            shapesArr = (JArray)shapes["Triangles"];
            LoadTriangles(shapesArr, db);
            shapesArr = (JArray)shapes["Rectangles"];
            LoadRectangles(shapesArr, db);
            LoadMaterials((JObject)dbDict["Materials"],db);
            LoadLights((JObject)dbDict["Lights"], db);
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

        private static List<Vector3> ParseVector3s(JArray jArray)
        {
            List<Vector3> vector3s = new List<Vector3>();
            foreach (JValue obj in jArray)
            {
                vector3s.Add(ParseVector3((string)obj));
            }
            return vector3s;

        }


        private static List<float> ParseFloats(JArray jArray)
        {
            List<float> floats = new List<float>();
            foreach (JValue obj in jArray)
            {
                floats.Add((float)obj);
            }
            return floats;
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
            bool isOrtho = (bool)cameraDict["isOrthographic"];
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


        private static void LoadSpheres(JArray spheres, SceneDatabase db)
        {
            foreach (var sphere in spheres)
            {
                LoadSphere((JObject)sphere, db);
            }
        }

        private static void LoadRectangles(JArray rectangles, SceneDatabase db)
        {
            foreach (var rectangle in rectangles)
            {
                LoadRectangle((JObject)rectangle, db);
            }
        }


        private static void LoadTriangles(JArray triangles, SceneDatabase db)
        {
            foreach (var triangle in triangles)
            {
                LoadTriangle((JObject)triangle, db);
            }
        }

        private static void LoadSphere(JObject sphereDict, SceneDatabase db)
        {
            Sphere sphere = new Sphere((int)sphereDict["id"], (int)sphereDict["materialId"],
                ParseVector3((string)sphereDict["center"]),
                (float)sphereDict["radius"]);
            db.MyShapes.Add(sphere);
        }

        private static void LoadRectangle(JObject rectDict, SceneDatabase db)
        {
            Rectangle rectangle = new Rectangle((int)rectDict["id"], (int)rectDict["materialId"],
                ParseVector3((string)rectDict["vertexA"]),
                ParseVector3((string)rectDict["vertexB"]),
                ParseVector3((string)rectDict["vertexC"]),
                ParseVector3((string)rectDict["vertexD"]));
            db.MyShapes.Add(rectangle);
        }
        private static void LoadTriangle(JObject triangleDict, SceneDatabase db)
        {
            Triangle triangle = new Triangle((int)triangleDict["id"], (int)triangleDict["materialId"],
                ParseVector3((string)triangleDict["vertexA"]),
                ParseVector3((string)triangleDict["vertexB"]),
                ParseVector3((string)triangleDict["vertexC"]));
            db.MyShapes.Add(triangle);
        }

        private static void LoadMaterials(JObject materials, SceneDatabase db)
        {
            db.MyMaterials = new List<Material>();
            LoadColorMaterials((JArray)materials["ColorMaterials"], db);
        }

        private static void LoadColorMaterials(JArray colorMatArr, SceneDatabase db)
        {
            foreach (JObject colorMat in colorMatArr)
            {
                LoadColorMaterial(colorMat, db);
            }
        }

        private static void LoadColorMaterial(JObject colorMatDict, SceneDatabase db)
        {
            ColorMaterial material = new ColorMaterial((int)colorMatDict["id"],
                ParseFloats((JArray)colorMatDict["specularities"]), (MaterialType)(int)colorMatDict["type"],
                ParseVector3s((JArray)colorMatDict["ambientColors"]), ParseVector3s((JArray)colorMatDict["diffuseColors"]),
                ParseVector3s((JArray)colorMatDict["specularColors"]));
            db.MyMaterials.Add(material);
        }

        private static void LoadLights(JObject lightDict, SceneDatabase db)
        {
            db.MyLights = new List<Light>();
            LoadDirectionalLights((JArray)lightDict["DirectionalLights"], db);
            LoadPointLights((JArray)lightDict["PointLights"], db);
            LoadSpotLights((JArray)lightDict["SpotLights"], db);
        }

        private static void LoadDirectionalLights(JArray lightArr,SceneDatabase db)
        {
            foreach(JObject light in lightArr)
            {
                LoadDirectionalLight(light,db);
            }
        }

        private static void LoadPointLights(JArray lightArr,SceneDatabase db)
        {
            foreach (JObject light in lightArr)
            {
                LoadPointLight(light,db);
            }
        }

        private static void LoadSpotLights(JArray lightArr, SceneDatabase db)
        {
            foreach(JObject light in lightArr)
            {
                LoadSpotLight(light,db);
            }
        }

        private static void LoadDirectionalLight(JObject dirLightDict,SceneDatabase db)
        {
            DirectionalLight light = new DirectionalLight((int)dirLightDict["id"],
                ParseVector3((string)dirLightDict["Direction"]), ParseVector3((string)dirLightDict["Color"]));
            db.MyLights.Add(light);
        }

        private static void LoadPointLight(JObject pointLightDict, SceneDatabase db)
        {
            PointLight light = new PointLight((int)pointLightDict["id"], new Vector3(), ParseVector3((string)pointLightDict["Color"]),
                ParseVector3((string)pointLightDict["Origin"]));
            db.MyLights.Add(light);
        }

        private static void LoadSpotLight(JObject spotLightDict, SceneDatabase db)
        {
            SpotLight light = new SpotLight((int)spotLightDict["id"], ParseVector3((string)spotLightDict["Direction"]),
                ParseVector3((string)spotLightDict["Color"]), ParseVector3((string)spotLightDict["Origin"]),
                (float)spotLightDict["InnerAngle"], (float)spotLightDict["OuterAngle"], (float)spotLightDict["FallOff"]);
            db.MyLights.Add(light);
        }
    }
}
