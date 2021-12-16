﻿using RT_CS.shapes;
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

        public int GetId()
        {
            return id;
        }
        public Material(int mid, List<float> spcs,MaterialType mt)
        {
            id = mid;
            specularities = spcs;
            type = mt;
        }

        public abstract Vector3 GetAmbientColor(int sid, Vector3 point);
        public abstract Vector3 GetDiffuseColor(int sid, Vector3 point);
        public abstract Vector3 GetSpecularColor(int sid, Vector3 point);
        public abstract float GetSpecularity(int sid, Vector3 point);

    }
}
