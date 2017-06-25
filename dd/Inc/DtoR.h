__inline double DegreesToRadians(double x)  { return (((x)/360.0) * (2.0 * 3.1415926535)); }
__inline double GeographicToGeometric(double x) { return -(x - 90.0); }
__inline double RadiansToDegrees(double a)  { return ((a) / 3.1415926535) * 180.0; }
__inline double GeometricToGeographic(double x) { return -(x - 90.0); }
