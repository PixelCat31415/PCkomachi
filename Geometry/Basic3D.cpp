// (FP)
// add Point*scalar when using proj
struct Point { double x = 0, y = 0, z = 0; };
Point operator-(Point p1, Point p2)
{return Point{p1.x-p2.x, p1.y-p2.y, p1.z-p2.z};}
Point operator+(Point p1, Point p2)
{return Point{p1.x+p2.x, p1.y+p2.y, p1.z+p2.z};}
Point operator/(Point p1, double v)
{ return Point{p1.x / v, p1.y / v, p1.z / v}; }
Point operator^(Point p1, Point p2) {
  return Point{p1.y * p2.z - p1.z * p2.y,
    p1.z * p2.x - p1.x * p2.z,
    p1.x * p2.y - p1.y * p2.x};
}
double operator*(Point p1, Point p2)
{ return p1.x * p2.x + p1.y * p2.y + p1.z * p2.z; }
double abs(Point a) { return sqrt(a * a); }
Point cross3(Point a, Point b, Point c)
{ return (b - a) ^ (c - a); }
double area2(Point a, Point b, Point c)
{ return abs(cross3(a, b, c)); }
double volume(Point a, Point b, Point c, Point d)
{ return cross3(a, b, c) * (d - a); }
Point masscenter(Point a, Point b, Point c, Point d)
{ return (a + b + c + d) / 4; }
PT proj(Point a, Point b, Point c, Point u) {
// proj. u to the plane of a, b, and c
  Point e1 = b - a;
  Point e2 = c - a;
  e1 = e1 / abs(e1);
  e2 = e2 - e1 * (e2 * e1);
  e2 = e2 / abs(e2);
  Point p = u - a;
  return PT{p * e1, p * e2};
}
