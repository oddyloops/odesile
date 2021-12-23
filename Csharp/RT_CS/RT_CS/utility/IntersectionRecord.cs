using System;
using System.Collections.Generic;
using System.Text;

namespace RT_CS.utility
{
    public class IntersectionRecord
    {
        public Vector3 Point { get; set; }
        public float Distance { get; set; } = float.MaxValue;
        public int ShapeId { get; set; }
        public bool  Hit { get; set; }
        public int ExceptId { get; set; } = -1;

    }
}
