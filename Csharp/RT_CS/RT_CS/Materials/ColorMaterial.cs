using RT_CS.shapes;
using RT_CS.utility;
using System;
using System.Collections.Generic;
using System.Text;

namespace RT_CS.Materials
{
    public class ColorMaterial : Material
    {
        private List<Vector3> ambientColors, diffuseColors, specularColors;
   
        public ColorMaterial(int mid, List<float> spcs, MaterialType mt, List<float> refl, List<float> trans, List<float> refr, List<Vector3> ac,List<Vector3> dc, List<Vector3> sc) : base(mid,spcs,mt,refl,trans,refr)
        {
            ambientColors = ac;
            diffuseColors = dc;
            specularColors = sc;
        }
        public override Vector3 GetAmbientColor(int sid, Vector3 point)
        {
            return ambientColors[0];
        }

        public override Vector3 GetDiffuseColor(int sid, Vector3 point)
        {
            return diffuseColors[0];
        }

        public override Vector3 GetSpecularColor(int sid, Vector3 point)
        {
            return specularColors[0];
        }

        public override float GetSpecularity(int sid, Vector3 point)
        {
            return specularities[0];
        }

        public override float GetReflectivity(int sid, Vector3 point)
        {
            return reflectivity[0];
        }
        public override float GetTransparency(int sid, Vector3 point)
        {
            return transparency[0];
        }
        public override float GetRefractiveIndex(int sid, Vector3 point)
        {
            return refractiveIndices[0];    
        }
    }
}
