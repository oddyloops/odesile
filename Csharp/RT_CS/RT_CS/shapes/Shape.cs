using RT_CS.Cameras;
using RT_CS.utility;
using RT_CS.Lights;
using RT_CS.Materials;
using System;
using System.Collections.Generic;
using System.Text;

namespace RT_CS.shapes
{
    public abstract class Shape
    {
        protected int sid;
        protected int materialId;

        public Shape(int id, int mid)
        {
            sid = id;
            materialId = mid;
        }

        public int GetMid()
        {
            return materialId;
        }

        public int GetId()
        {
            return sid;
        }
        private void IntersectShapes(Ray r, IntersectionRecord record, List<Shape> shapes)
        {
            foreach (Shape s in shapes)
            {
                s.Intersect(r, record);
            }
        }

       

        public abstract Vector3 GetNormal(Vector3 point);
        public abstract void Intersect(Ray r,IntersectionRecord intersection);
        public virtual Vector3 Paint(IntersectionRecord record, List<Light> lighting, Vector3 ambientLight, Vector3 viewDirection,
            int generation,List<Shape> shapes, List<Material> materials)
        {
             Shape GetShapeById(int id)
            {
                foreach (Shape shape in shapes)
                {
                    if (id == shape.GetId())
                        return shape;
                }
                return null;
            }

             Material GetMaterialById(int id)
            {
                foreach (Material material in materials)
                {
                    if (id == material.GetId())
                        return material;
                }
                return null;
            }
            Material mat = GetMaterialById(materialId);
            Vector3 ambientColor = mat.GetAmbientColor(sid, record.Point);
            Vector3 diffuseColor = mat.GetDiffuseColor(sid, record.Point);
            Vector3 specularColor = mat.GetSpecularColor(sid, record.Point);
            float specularity = mat.GetSpecularity(sid, record.Point);

            Vector3 color;
            color.x = 0;
            color.y = 0;
            color.z = 0;

            foreach (Light lit in lighting)
                color += LightupMaterial(lit, record, ambientColor, diffuseColor, specularColor, specularity, ambientLight, viewDirection);

            color.x = MathF.Max(0,MathF.Min(1, color.x));
            color.y = MathF.Max(0,MathF.Min(1, color.y));
            color.z = MathF.Max(0,MathF.Min(1, color.z));

            Vector3 reflectivecolor, refractivecolor;
            reflectivecolor.x = 0;
            reflectivecolor.y = 0;
            reflectivecolor.z = 0;

            refractivecolor.x = 0;
            refractivecolor.y = 0;
            refractivecolor.z = 0;

            Vector3 reverseView = -1 * viewDirection;

            if (generation > 0)
            {
                float reflect = mat.GetReflectivity(sid, record.Point);
                float transparent = mat.GetTransparency(sid, record.Point);
                float refractiveIndex = mat.GetRefractiveIndex(sid, record.Point);
                Vector3 normal = GetNormal(record.Point);

                if (reflect > 0)
                {
                    Vector3 reverseddir = (((2 * Vector3.Dot(reverseView, normal)) * normal) - (reverseView)).Normalize();
                    Ray r;
                    r.posit = record.Point;
                    r.direct = reverseddir;
                    IntersectionRecord reflectRec = new IntersectionRecord();
                    reflectRec.ExceptId = sid;
                    IntersectShapes(r, reflectRec, shapes);

                    if (reflectRec.Hit)
                    {
                        Shape reflectShape = GetShapeById(reflectRec.ShapeId);
                        reflectivecolor = reflectShape.Paint(reflectRec, lighting, ambientLight, reverseddir, generation - 1, shapes, materials);
                    }
                }

                if (transparent > 0)
                {
                    float cosIncidence = Vector3.Dot(normal, reverseView);
                    float sinIncidence = MathF.Sin(MathF.Acos(cosIncidence));
                    float sinRefractive = sinIncidence / refractiveIndex;
                    Vector3 refractedDirection = (-1 * ((reverseView/refractiveIndex) + (MathF.Cos(MathF.Asin(sinRefractive)) - (cosIncidence/refractiveIndex)) * normal)).Normalize();

                    Ray r;
                    r.posit = record.Point;
                    r.direct = refractedDirection;
                    IntersectionRecord refractRec = new IntersectionRecord();
                    refractRec.ExceptId = sid;
                    IntersectShapes(r, refractRec, shapes);

                    if (refractRec.Hit)
                    {
                        Shape refractShape = GetShapeById(refractRec.ShapeId);
                        refractivecolor = refractShape.Paint(refractRec, lighting, ambientLight, refractedDirection, generation - 1, shapes, materials);
                    }
                }
            }
            if (generation > 0)
                color = ((color * (1 - mat.GetReflectivity(sid, record.Point) - mat.GetTransparency(sid, record.Point))) + (mat.GetReflectivity(sid, record.Point) * reflectivecolor) + (mat.GetTransparency(sid, record.Point) * refractivecolor));

            return color;
        }

        private Vector3 LightupMaterial (Light lit, IntersectionRecord record, Vector3 ambientColor, Vector3 diffuseColor, Vector3 SpecularColor, float specularity, Vector3 ambientLight, Vector3 viewDirection)
        {
            Vector3 norm = GetNormal(record.Point);
            Vector3 reverseLight = -1 * lit.GetDirection(record.Point);
            Vector3 halfway = (viewDirection + reverseLight) * 0.5f;
            Vector3 lightColor = lit.GetColor(record.Point);
            float specularMult = MathF.Pow(Vector3.Dot(norm, halfway), specularity);
            float diffuseMult = Vector3.Dot(reverseLight, norm); 

            return Vector3.Mult(ambientLight,ambientColor) + diffuseMult * Vector3.Mult(lightColor ,diffuseColor) + specularMult * Vector3.Mult(lightColor, SpecularColor);
        }

    }

}
