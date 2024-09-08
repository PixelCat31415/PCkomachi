//Union of Circles
vector<pair<double, double>> CoverSegment(Cir a, Cir b) {
  double d = abs(a.o - b.o);
  vector<pair<double, double>> res;
  if (sign(a.r + b.r - d) == 0);
  else if (d <= abs(a.r - b.r) + eps) {
    if (a.r < b.r) res.emplace_back(0, 2 * pi);
  } else if (d < abs(a.r + b.r) - eps) {
    double o = acos((a.r * a.r + d * d - b.r * b.r) / (2 * a.r * d)), z = atan2((b.o - a.o).Y, (b.o - a.o).X);
    if (z < 0) z += 2 * pi;
    double l = z - o, r = z + o;
    if (l < 0) l += 2 * pi;
    if (r > 2 * pi) r -= 2 * pi;
    if (l > r) res.emplace_back(l, 2 * pi), res.emplace_back(0, r);
    else res.emplace_back(l, r);
  }
  return res;
}
double CircleUnionArea(vector<Cir> c) { // circle should be identical
  int n = c.size();
  double a = 0, w;
  for (int i = 0; w = 0, i < n; ++i) {
    vector<pair<double, double>> s = {{2 * pi, 9}}, z;
    for (int j = 0; j < n; ++j) if (i != j) {
      z = CoverSegment(c[i], c[j]);
      for (auto &e : z) s.push_back(e);
    }
    sort(s.begin(), s.end());
    auto F = [&] (double t) { return c[i].r * (c[i].r * t + c[i].o.X * sin(t) - c[i].o.Y * cos(t)); };
    for (auto &e : s) {
      if (e.first > w) a += F(e.first) - F(w);
      w = max(w, e.second);
    }
  }
  return a * 0.5;
}
// Union of Polygons
double polyUnion(vector <vector <Pt>> poly) {
  int n = poly.size();
  double ans = 0;
  auto solve = [&](Pt a, Pt b, int cid) {
    vector <pair <Pt, int>> event;
    for (int i = 0; i < n; ++i) {
      int st = 0, sz = poly[i].size();
      while (st < sz && ori(poly[i][st], a, b) != 1) st++;
      if (st == sz) continue;
      for (int j = 0; j < sz; ++j) {
        Pt c = poly[i][(j + st) % sz], d = poly[i][(j + st + 1) % sz];
        if (sign((a - b) ^ (c - d)) != 0) {
          int ok1 = ori(c, a, b) == 1, ok2 = ori(d, a, b) == 1;
          if (ok1 ^ ok2) event.emplace_back(LinesInter({a, b}, {c, d}), ok1 ? 1 : -1);
        } else if (ori(c, a, b) == 0 && sign((a - b) * (c - d)) > 0 && i <= cid) {
          event.emplace_back(c, -1);
          event.emplace_back(d, 1);
        }
      }
    }
    sort(all(event), [&](pair <Pt, int> i, pair <Pt, int> j) {
      return ((a - i.first) * (a - b)) < ((a - j.first) * (a - b));
    });
    int now = 0;
    Pt lst = a;
    for (auto [x, y] : event) {
      if (btw(a, b, lst) && btw(a, b, x) && !now) ans += lst ^ x;
      now += y, lst = x;
    }
  };
  for (int i = 0; i < n; ++i) for (int j = 0; j < poly[i].size(); ++j) {
    solve(poly[i][j], poly[i][(j + 1) % int(poly[i].size())], i);
  }
  return ans / 2;
}
