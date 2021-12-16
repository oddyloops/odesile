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

        public abstract Vector3 GetNormal(Vector3 point);
        public abstract void Intersect(Ray r,IntersectionRecord intersection);
        public virtual Vector3 Paint(IntersectionRecord record, List<Light> lighting, Material mat, Vector3 ambientLight, Vector3 viewDirection)
        {
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
