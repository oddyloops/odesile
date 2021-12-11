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
        protected List<float> specularities;
        protected MaterialType type;

        public Material(int mid, List<float> spcs,MaterialType mt)
        {
            id = mid;
            specularities = spcs;
            type = mt;
        }

        public abstract Vector3 GetAmbientColor(Shape s, Vector3 point);
        public abstract Vector3 GetDiffuseColor(Shape s, Vector3 point);
        public abstract Vector3 GetSpecularColor(Shape s, Vector3 point);
        public abstract float GetSpecularity(Shape s, Vector3 point);

    }
}
