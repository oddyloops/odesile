using RT_CS.shapes;
using RT_CS.utility;
using System;
using System.Collections.Generic;
using System.Text;

namespace RT_CS.Materials
{
    public class ColorMaterial : Material
    {
        private List<Vector3> ambientColors;
        private List<Vector3> diffuseColors;
        private List<Vector3> specularColors;
        public ColorMaterial(int mid, List<float> spcs, MaterialType mt,List<Vector3> ac,List<Vector3> dc, List<Vector3> sc) : base(mid,spcs,mt)
        {
            ambientColors = ac;
            diffuseColors = dc;
            specularColors = sc;
        }
        public override Vector3 GetAmbientColor(Shape s, Vector3 point)
        {
            return ambientColors[0];
        }

        public override Vector3 GetDiffuseColor(Shape s, Vector3 point)
        {
            return diffuseColors[0];
        }

        public override Vector3 GetSpecularColor(Shape s, Vector3 point)
        {
            return specularColors[0];
        }

        public override float GetSpecularity(Shape s, Vector3 point)
        {
            return specularities[0];
        }
    }
}
