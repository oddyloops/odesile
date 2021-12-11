using RT_CS.utility;
using System;
using System.Collections.Generic;
using System.Text;

namespace RT_CS.Lights
{
    public abstract class Light
    {
        protected int id;
        protected Vector3 direction;
        protected Vector3 color;

        public Light(int lid, Vector3 d,Vector3 c)
        {
            id = lid;
            direction = d.Normalize();
            color = c;
        }

        public abstract Vector3 GetDirection(Vector3 point);

        public virtual Vector3 GetColor(Vector3 point)
        {
            return color;
        }
    }
}
