using RT_CS.utility;
using System;
using System.Collections.Generic;
using System.Text;

namespace RT_CS.Materials
{
    public class TextureMaterial : Material
    {

        private List<Vector3> ambientColors, specularColors;
        private List<Texture> diffuseColors;

        public TextureMaterial(int mid, List<float> spcs, MaterialType mt, List<float> refl, List<float> trans, List<float> refr,
            List<Vector3> ac, List<Texture> dc, List<Vector3> sc) : base(mid, spcs, mt, refl, trans, refr)
        {
            ambientColors = ac;
            diffuseColors = dc;
            specularColors = sc;

        }

        public override Vector3 GetAmbientColor(Vector2 uv)
        {
            return ambientColors[0];
        }

        public override Vector3 GetDiffuseColor(Vector2 uv)
        {
            return diffuseColors[0].GetPixel(uv);
        }

        public override Vector3 GetSpecularColor(Vector2 uv)
        {
            return specularColors[0];
        }

        public override float GetSpecularity(Vector2 uv)
        {
            return specularities[0];
        }

        public override float GetReflectivity(Vector2 uv)
        {
            return reflectivity[0];
        }
        public override float GetTransparency(Vector2 uv)
        {
            return transparency[0];
        }
        public override float GetRefractiveIndex(Vector2 uv)
        {
            return refractiveIndices[0];
        }
    }
}
