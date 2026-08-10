PT unit(PT p) { return p / abs(p); }
PT ccw(PT p, double t) {
  return PT(
    p.x * cos(t) - p.y * sin(t),
    p.x * sin(t) + p.y * cos(t)
  );
}
vector<Line> tangent(Cir c, PT p) {
  vector<Line> z;
  double d = abs(p - c.o);
  if (sign(d - c.r) == 0) {
    z.push_back({p, p + ccw90(p - c.o)});
  } else if (d > c.r) {
    double o = acos(c.r / d);
    PT i = unit(p - c.o), j = ccw(i, o) * c.r, k = ccw(i, -o) * c.r;
    z.push_back({c.o + j, p});
    z.push_back({c.o + k, p});
  }
  return z;
}
vector <Line> tangent(Cir c1, Cir c2, int sign1) {
  // sign1 = 1 for outer tang, -1 for inter tang
  vector <Line> ret;
  double d_sq = abs2(c1.o - c2.o);
  if (sign(d_sq) == 0) return ret;
  double d = sqrt(d_sq);
  PT v = (c2.o - c1.o) / d;
  double c = (c1.r - sign1 * c2.r) / d;
  if (c * c > 1) return ret;
  double h = sqrt(max(0.0, 1.0 - c * c));
  for (int sign2 = 1; sign2 >= -1; sign2 -= 2) {
    PT n = PT(v.X * c - sign2 * h * v.Y, v.Y * c + sign2 * h * v.X);
    PT p1 = c1.o + n * c1.r;
    PT p2 = c2.o + n * (c2.r * sign1);
    if (sign(p1.X - p2.X) == 0 && sign(p1.Y - p2.Y) == 0)
      p2 = p1 + ccw90(c2.o - c1.o);
    ret.pb({p1, p2});
  }
  return ret;
}