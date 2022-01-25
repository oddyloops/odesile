using RT_CS.shapes;
using RT_CS.utility;
using System;
using System.Collections.Generic;
using System.Text;

namespace RT_CS.Materials
{
    public abstract class Material
    {
        protected int id;
        protected List<float> specularities, reflectivity, transparency, refractiveIndices;
        protected MaterialType type;

        public int GetId()
        {
            return id;
        }
        public Material(int mid, List<float> spcs,MaterialType mt, List<float> refl, List<float> trans, List<float> refr)
        {
            id = mid;
            specularities = spcs;
            type = mt;
            reflectivity = refl;
            transparency = trans;
            refractiveIndices = refr;
        }

        public abstract Vector3 GetAmbientColor(Vector2 uv);
        public abstract Vector3 GetDiffuseColor(Vector2 uv);
        public abstract Vector3 GetSpecularColor(Vector2 uv);
        public abstract float GetSpecularity(Vector2 uv);
        public abstract float GetReflectivity(Vector2 uv);
        public abstract float GetTransparency(Vector2 uv);
        public abstract float GetRefractiveIndex(Vector2 uv);


    }
}
