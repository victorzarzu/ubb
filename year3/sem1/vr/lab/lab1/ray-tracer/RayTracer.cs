using System;
using System.Runtime.InteropServices;

namespace rt
{
    class RayTracer
    {
        private Geometry[] geometries;
        private Light[] lights;

        public RayTracer(Geometry[] geometries, Light[] lights)
        {
            this.geometries = geometries;
            this.lights = lights;
        }

        private double ImageToViewPlane(int n, int imgSize, double viewPlaneSize)
        {
            var u = n * viewPlaneSize / imgSize;
            u -= viewPlaneSize / 2;
            return u;
        }

        private Intersection FindFirstIntersection(Line ray, double minDist, double maxDist)
        {
            var intersection = new Intersection();

            foreach (var geometry in geometries)
            {
                var intr = geometry.GetIntersection(ray, minDist, maxDist);

                if (!intr.Valid || !intr.Visible) continue;

                if (!intersection.Valid || !intersection.Visible)
                {
                    intersection = intr;
                }
                else if (intr.T < intersection.T)
                {
                    intersection = intr;
                }
            }

            return intersection;
        }
        
        // private bool IsPointInSphere(Vector point, Geometry geometry) {
        //     if(geometry is Sphere) {
        //         Sphere sphere = (Sphere) geometry;

        //         return (point.X - sphere.Center.X) * (point.X - sphere.Center)
        //     }
        //     return true;
        // }

        private bool IsLit(Vector point, Light light)
        {
            // ADD CODE HERE: Detect whether the given point has a clear line of sight to the given light
            var intersectionPosition = FindFirstIntersection(new Line(light.Position, point), 0, 1000).Position;

            return Math.Abs(intersectionPosition.X - point.X) <= 0.00001 && Math.Abs(intersectionPosition.Y - point.Y) <= 0.00001 && Math.Abs(intersectionPosition.Z - point.Z) <= 0.00001;
        }

        public void Render(Camera camera, int width, int height, string filename)
        {
            var background = new Color();
            var viewParallel = (camera.Up ^ camera.Direction).Normalize();

            var image = new Image(width, height);

            var vecW = camera.Direction * camera.ViewPlaneDistance;
            for (var i = 0; i < width; i++)
            {
                for (var j = 0; j < height; j++)
                {
                    Vector dir = camera.Position + vecW + camera.Up * ImageToViewPlane(j, height, camera.ViewPlaneHeight) + 
                            viewParallel * ImageToViewPlane(i, width, camera.ViewPlaneWidth);
                    
                    Intersection intersection = FindFirstIntersection(new Line(camera.Position, dir), 0, 1000);
                    if(intersection.Geometry == null) {
                        image.SetPixel(i, j, background);
                        continue;
                    }

                    Material material = intersection.Geometry.Material;
                    Color color = new Color();
                    foreach (var light in lights) {
                        bool isLit = IsLit(intersection.Position, light);
                        var T = new Vector(light.Position - intersection.Position).Normalize();
                        var E = new Vector(camera.Position - intersection.Position).Normalize();
                        var N = intersection.Geometry.Normal(intersection.Position);
                        var R = (N * (N * T) * 2 - T).Normalize();

                        Color color_light = material.Ambient * light.Ambient;
                        if(!isLit) {
                            color += color_light;
                            color_light *= light.Intensity;
                            continue;
                        }
                        if(N * T > 0) {
                            color_light += material.Diffuse * light.Diffuse * (N * T);
                        }
                        if(E * R > 0) {
                            color_light += material.Specular * light.Specular * Math.Pow(E * R, material.Shininess);
                        }
                        color_light *= light.Intensity;
                        color += color_light;
                    }

                    image.SetPixel(i, j, color);
                }
            }

            image.Store(filename);
        }
    }
}