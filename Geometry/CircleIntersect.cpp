// (FP)
// lines are nondegenerate; polygons have no zero edges
vector<PT> CircleLineInter(Cir c, Line l) {
  PT p = l.a + (l.b - l.a) *
    ((c.o - l.a) * (l.b - l.a)) /
    abs2(l.b - l.a);
  double s = (l.b - l.a) ^ (c.o - l.a);
  double h2 = c.r * c.r - s * s /
    abs2(l.b - l.a);
  if (sign(h2) == -1) return {};
  if (sign(h2) == 0) return {p};
  PT h = (l.b - l.a) / abs(l.b - l.a) * sqrt(h2);
  return {p - h, p + h};
}
vector<PT> CirclesInter(Cir c1, Cir c2) {
  double d2 = abs2(c1.o - c2.o), d = sqrt(d2);
  if (sign(d2) == 0) return {}; // concentric circles
  if (d < max(c1.r, c2.r) - min(c1.r, c2.r) ||
      d > c1.r + c2.r) return {};
  PT u = (c1.o + c2.o) / 2 + (c1.o - c2.o) *
    ((c2.r * c2.r - c1.r * c1.r) / (2 * d2));
  double A = sqrt((c1.r + c2.r + d) *
    (c1.r - c2.r + d) * (c1.r + c2.r - d) *
    (-c1.r + c2.r + d));
  PT v = PT{c1.o.y - c2.o.y, -c1.o.x + c2.o.x}
    * A / (2 * d2);
  if (sign(v.x) == 0 && sign(v.y) == 0) return {u};
  return {u + v, u - v};
}
double _area(PT pa, PT pb, double r) {
  if (abs(pa) < abs(pb)) swap(pa, pb);
  if (abs(pb) < EPS) return 0;
  double S, h, theta;
  double a = abs(pb), b = abs(pa), c = abs(pb - pa);
  double cosB = pb * (pb - pa) / a / c, B = acos(cosB);
  double cosC = (pa * pb) / a / b, C = acos(cosC);
  if (a > r) {
    S = (C / 2) * r * r;
    h = a * b * sin(C) / c;
    if (h < r && B < numbers::pi / 2)
      S -= acos(h / r) * r * r -
        h * sqrt(r * r - h * h);
  } else if (b > r) {
    theta = numbers::pi - B - asin(sin(B) / r * a);
    S = .5 * a * r * sin(theta) +
      (C - theta) / 2 * r * r;
  } else S = .5 * sin(C) * a * b;
  return S;
}
double AreaPolyCircle(vector<PT> poly, PT O,
                        double r) {
  double S = 0; int n = sz(poly);
  for (int i = 0; i < n; ++i)
    S += _area(poly[i] - O, poly[(i + 1) % n] - O,
      r) * ori(O, poly[i], poly[(i + 1) % n]);
  return fabs(S);
}
