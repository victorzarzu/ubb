using System;
using System.Drawing;
using System.IO;
using System.Text.RegularExpressions;

namespace rt;

public class RawCtMask: Geometry
{
    private readonly Vector _position;
    private readonly double _scale;
    private readonly ColorMap _colorMap;
    private readonly byte[] _data;

    private readonly int[] _resolution = new int[3];
    private readonly double[] _thickness = new double[3];
    private readonly Vector _v0;
    private readonly Vector _v1;

    public RawCtMask(string datFile, string rawFile, Vector position, double scale, ColorMap colorMap) : base(Color.NONE)
    {
        _position = position;
        _scale = scale;
        _colorMap = colorMap;

        var lines = File.ReadLines(datFile);
        foreach (var line in lines)
        {
            var kv = Regex.Replace(line, "[:\\t ]+", ":").Split(":");
            if (kv[0] == "Resolution")
            {
                _resolution[0] = Convert.ToInt32(kv[1]);
                _resolution[1] = Convert.ToInt32(kv[2]);
                _resolution[2] = Convert.ToInt32(kv[3]);
            } else if (kv[0] == "SliceThickness")
            {
                _thickness[0] = Convert.ToDouble(kv[1]);
                _thickness[1] = Convert.ToDouble(kv[2]);
                _thickness[2] = Convert.ToDouble(kv[3]);
            }
        }

        _v0 = position;
        _v1 = position + new Vector(_resolution[0]*_thickness[0]*scale, _resolution[1]*_thickness[1]*scale, _resolution[2]*_thickness[2]*scale);

        var len = _resolution[0] * _resolution[1] * _resolution[2];
        _data = new byte[len];
        using FileStream f = new FileStream(rawFile, FileMode.Open, FileAccess.Read);
        if (f.Read(_data, 0, len) != len)
        {
            throw new InvalidDataException($"Failed to read the {len}-byte raw data");
        }
    }
    
    private ushort Value(int x, int y, int z)
    {
        if (x < 0 || y < 0 || z < 0 || x >= _resolution[0] || y >= _resolution[1] || z >= _resolution[2])
        {
            return 0;
        }

        return _data[z * _resolution[1] * _resolution[0] + y * _resolution[0] + x];
    }

    public override Intersection GetIntersection(Line line, double minDist, double maxDist)
    {
        double voxelSize = 0.2;
        Vector rayOrigin = line.X0;
        Vector rayDirection = line.Dx;

        double tMin = (_v0.X - rayOrigin.X) / rayDirection.X;
        double tMax = (_v1.X - rayOrigin.X) / rayDirection.X;
        double tyMin = (_v0.Y - rayOrigin.Y) / rayDirection.Y;
        double tyMax = (_v1.Y - rayOrigin.Y) / rayDirection.Y;
        double tzMin = (_v0.Z - rayOrigin.Z) / rayDirection.Z;
        double tzMax = (_v1.Z - rayOrigin.Z) / rayDirection.Z;

        if (tMin > tMax)
        {
            (tMin, tMax) = (tMax, tMin); 
        }

        if (tyMin > tyMax) {
            (tyMin, tyMax) = (tyMax, tyMin); 
        }

        if ((tMin > tyMax) || (tyMin > tMax)) {
            return Intersection.NONE;
        }
        tMin = Math.Max(tMin, tyMin);
        tMax = Math.Min(tMax, tyMax);

        if (tzMin > tzMax) {
            (tzMin, tzMax) = (tzMax, tzMin);
        }

        if ((tMin > tzMax) || (tzMin > tMax)) {
            return Intersection.NONE;
        }
        tMin = Math.Max(tMin, tzMin);
        tMax = Math.Min(tMax, tzMax);

        Vector currentPosition = rayOrigin + rayDirection * tMin;
        Color color = Color.NONE;
        double opacity = 0;

        if(tMin >= tMax && tMax < minDist && tMin > maxDist) {
            return Intersection.NONE;
        }
        while (tMin <= tMax)
        {
            int[] voxelIndex = GetIndexes(currentPosition);
            ushort value = Value(voxelIndex[0], voxelIndex[1], voxelIndex[2]);
            if (value > 0)
            {
                double t = tMin;
                Vector initPosition = currentPosition;
                while(tMin <= tMax && opacity <= 0.99) {
                    voxelIndex = GetIndexes(currentPosition);
                    value = Value(voxelIndex[0], voxelIndex[1], voxelIndex[2]);
                    if(value <= 0) {
                        currentPosition += rayDirection * voxelSize;
                        tMin += voxelSize;
                        continue;
                    }
                    Color current_color = GetColor(currentPosition);
                    double voxelOpacity = current_color.Alpha;

                    color += current_color * (1 - opacity) * voxelOpacity;
                    opacity += (1 - opacity) * voxelOpacity;
                    if(opacity >= 0.99) {
                        break;
                    }
                    currentPosition += rayDirection * voxelSize;
                    tMin += voxelSize;
                }
                return new Intersection(true, true, this, line, t, GetNormal(initPosition), Material.FromColor(color), color);
            }
            currentPosition += rayDirection * voxelSize;
            tMin += voxelSize;
        }

        return Intersection.NONE;
    }
    
    private int[] GetIndexes(Vector v)
    {
        return new []{
            (int)Math.Floor((v.X - _position.X) / _thickness[0] / _scale), 
            (int)Math.Floor((v.Y - _position.Y) / _thickness[1] / _scale),
            (int)Math.Floor((v.Z - _position.Z) / _thickness[2] / _scale)};
    }
    private Color GetColor(Vector v)
    {
        int[] idx = GetIndexes(v);

        ushort value = Value(idx[0], idx[1], idx[2]);
        return _colorMap.GetColor(value);
    }

    private Vector GetNormal(Vector v)
    {
        int[] idx = GetIndexes(v);
        double x0 = Value(idx[0] - 1, idx[1], idx[2]);
        double x1 = Value(idx[0] + 1, idx[1], idx[2]);
        double y0 = Value(idx[0], idx[1] - 1, idx[2]);
        double y1 = Value(idx[0], idx[1] + 1, idx[2]);
        double z0 = Value(idx[0], idx[1], idx[2] - 1);
        double z1 = Value(idx[0], idx[1], idx[2] + 1);

        return new Vector(x1 - x0, y1 - y0, z1 - z0).Normalize();
    }
}