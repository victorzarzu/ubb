using System;


namespace rt
{
    public class Ellipsoid : Geometry
    {
        private Vector Center { get; }
        private Vector SemiAxesLength { get; }
        private double Radius { get; }
        
        
        public Ellipsoid(Vector center, Vector semiAxesLength, double radius, Material material, Color color) : base(material, color)
        {
            Center = center;
            SemiAxesLength = semiAxesLength;
            Radius = radius;
        }

        public Ellipsoid(Vector center, Vector semiAxesLength, double radius, Color color) : base(color)
        {
            Center = center;
            SemiAxesLength = semiAxesLength;
            Radius = radius;
        }

        private Vector Normal(Vector point) {
            return new Vector(
                2 * (point.X - Center.X) / (SemiAxesLength.X * SemiAxesLength.X),
                2 * (point.Y - Center.Y) / (SemiAxesLength.Y * SemiAxesLength.Y),
                2 * (point.Z - Center.Z) / (SemiAxesLength.Z * SemiAxesLength.Z)
            ).Normalize();
        }

        public override Intersection GetIntersection(Line line, double minDist, double maxDist)
        {
            var a = Math.Pow(line.Dx.X, 2) / Math.Pow(SemiAxesLength.X, 2) + 
                Math.Pow(line.Dx.Y, 2) / Math.Pow(SemiAxesLength.Y, 2) + 
                Math.Pow(line.Dx.Z, 2) / Math.Pow(SemiAxesLength.Z, 2);
            var b = 2 * (line.Dx.X * (line.X0.X - Center.X) / Math.Pow(SemiAxesLength.X, 2) + line.Dx.Y * (line.X0.Y - Center.Y) / Math.Pow(SemiAxesLength.Y, 2) + line.Dx.Z * (line.X0.Z - Center.Z) / Math.Pow(SemiAxesLength.Z, 2));
            var c = Math.Pow(line.X0.X - Center.X, 2) / Math.Pow(SemiAxesLength.X, 2)+ Math.Pow(line.X0.Y - Center.Y, 2) / Math.Pow(SemiAxesLength.Y, 2) + Math.Pow(line.X0.Z - Center.Z, 2) / Math.Pow(SemiAxesLength.Z, 2) - Math.Pow(this.Radius, 2);
            
            var delta = b * b - 4 * a * c;
            if(delta < 0) {
                return new Intersection(false, false, this, line, 0, new Vector());
            }

            var t1 = (-b + Math.Sqrt(delta)) / (2 * a);
            var t2 = (-b - Math.Sqrt(delta)) / (2 * a);

            if(t1 > t2) {
               var temp = t2;
               t2 = t1;
               t1 = temp; 
            }
            if(t1 > 0) {
                var X = line.X0 + line.Dx * t1;
                return new Intersection(true, true, this, line, t1, Normal(X));
            }
            if(t2 > 0) {
                var X = line.X0 + line.Dx * t2;
                return new Intersection(true, true, this, line, t2, Normal(X));
            }
            return new Intersection(false, false, this, line, 0, new Vector());
        }
    }
}
