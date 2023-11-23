using System;

namespace rt
{
    public class Sphere : Geometry
    {
        private Vector Center { get; set; }
        private double Radius { get; set; }

        public Sphere(Vector center, double radius, Material material, Color color) : base(material, color)
        {
            Center = center;
            Radius = radius;
        }

        public override Intersection GetIntersection(Line line, double minDist, double maxDist)
        {
            // var a = line.Dx.X * line.Dx.X + line.Dx.Y * line.Dx.Y + line.Dx.Z * line.Dx.Z;
            // var b = (line.Dx.X * line.X0.X - line.Dx.X * Center.X + line.Dx.Y * line.X0.Y - line.Dx.Y * Center.Y + line.Dx.Z * line.X0.Z - line.Dx.Z * Center.Z) * 2;
            // var c = line.X0.X * line.X0.X + line.X0.Y * line.X0.Y + line.X0.Z * line.X0.Z + Center.X * Center.X + Center.Y * Center.Y + Center.Z * Center.Z - 
            //        line.X0.X * Center.X * 2 - line.X0.Y * Center.Y * 2 - line.X0.Z * Center.Z * 2 - this.Radius * this.Radius;
            var a = Math.Pow(line.Dx.X, 2) + Math.Pow(line.Dx.Y, 2) + Math.Pow(line.Dx.Z, 2);
            var b = 2 * (line.Dx.X * (line.X0.X - Center.X) + line.Dx.Y * (line.X0.Y - Center.Y) + line.Dx.Z * (line.X0.Z - Center.Z));
            var c = Math.Pow(line.X0.X - Center.X, 2) + Math.Pow(line.X0.Y - Center.Y, 2) + Math.Pow(line.X0.Z - Center.Z, 2) - Math.Pow(this.Radius, 2);
            
            var delta = b * b - 4 * a * c;
            if(delta < 0) {
                return new Intersection(false, false, this, line, 0);
            }

            var t1 = (-b + Math.Sqrt(delta)) / (2 * a);
            var t2 = (-b - Math.Sqrt(delta)) / (2 * a);

            if(t1 > t2) {
               var temp = t2;
               t2 = t1;
               t1 = temp; 
            }
            if(t1 > 0) {
                return new Intersection(true, true, this, line, t1);
            }
            if(t2 > 0) {
                return new Intersection(true, true, this, line, t2);
            }
            return new Intersection(false, false, this, line, 0);

            var dist1 = line.CoordinateToPosition(t1).Length();
            var dist2 = line.CoordinateToPosition(t2).Length();

            if(minDist <= dist1 && dist1 <= maxDist && minDist <= dist2 && dist2 <= maxDist) {
                return new Intersection(true, true, this, line, dist1 < dist2 ? t1 : t2);
            }
            if(minDist <= dist1 && dist1 <= maxDist) {
                return new Intersection(true, true, this, line, t1);
            }
            if(minDist <= dist2 && dist2 <= maxDist) {
                return new Intersection(true, true, this, line, t2);
            }

            return new Intersection(false, false, this, line, 0);
        }

        public override Vector Normal(Vector v)
        {
            var n = v - Center;
            n.Normalize();
            return n;
        }
    }
}