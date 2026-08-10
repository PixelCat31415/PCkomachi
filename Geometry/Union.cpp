// (FP) needs segment intersect
// circles are pairwise distinct; polygons are CCW
vector<pair<double, double>>
CoverSegment(Cir a, Cir b) {
  double d = abs(a.o - b.o);
  vector<pair<double, double>> res;
  if (sign(a.r + b.r - d) == 0);
  else if (d <= abs(a.r - b.r) + EPS) {
    if (a.r < b.r)
      res.emplace_back(0, 2 * numbers::pi);
  } else if (d < abs(a.r + b.r) - EPS) {
    double o = acos((a.r * a.r + d * d - b.r * b.r)
      / (2 * a.r * d));
    double z = atan2((b.o - a.o).y, (b.o - a.o).x);
    if (z < 0) z += 2 * numbers::pi;
    double l = z - o, r = z + o;
    if (l < 0) l += 2 * numbers::pi;
    if (r > 2 * numbers::pi) r -= 2 * numbers::pi;
    if (l > r)
      res.emplace_back(l, 2 * numbers::pi),
      res.emplace_back(0, r);
    else res.emplace_back(l, r);
  }
  return res;
}
double CircleUnionArea(vector<Cir> c) {
  int n = sz(c);
  double a = 0, w;
  for (int i = 0; w = 0, i < n; ++i) {
    vector<pair<double, double>> s = {
      {2 * numbers::pi, 9}
    }, z;
    for (int j = 0; j < n; ++j) if (i != j) {
      z = CoverSegment(c[i], c[j]);
      for (auto &e : z) s.push_back(e);
    }
    sort(s.begin(), s.end());
    auto F = [&] (double t) {
      return c[i].r * (c[i].r * t +
        c[i].o.x * sin(t) - c[i].o.y * cos(t));
    };
    for (auto &e : s) {
      if (e.first > w) a += F(e.first) - F(w);
      w = max(w, e.second);
    }
  }
  return a * 0.5;
}
// Union of Polygons
double PolyUnion(vector<vector<PT>> poly) {
  int n = sz(poly);
  double ans = 0;
  auto solve = [&](PT a, PT b, int cid) {
    vector<pair<PT, int>> event;
    for (int i = 0; i < n; ++i) {
      int st = 0, m = sz(poly[i]);
      while (st < m && ori(poly[i][st], a, b) != 1)
        st++;
      if (st == m) continue;
      For(j, 0, m - 1) {
        PT c = poly[i][(j + st) % m];
        PT d = poly[i][(j + st + 1) % m];
        if (sign((a - b) ^ (c - d)) != 0) {
          int ok1 = ori(c, a, b) == 1;
          int ok2 = ori(d, a, b) == 1;
          if (ok1 ^ ok2)
            event.emplace_back(GetInter(a, b, c, d),
              ok1 ? 1 : -1);
        } else if (ori(c, a, b) == 0 &&
            sign((a - b) * (c - d)) > 0 && i <= cid) {
          event.emplace_back(c, -1);
          event.emplace_back(d, 1);
        }
      }
    }
    sort(iter(event), [&](pair<PT, int> i,
                          pair<PT, int> j) {
      return (a - i.first) * (a - b) <
        (a - j.first) * (a - b);
    });
    int now = 0;
    PT lst = a;
    for (auto [x, y] : event) {
      if (btw(a, b, lst) && btw(a, b, x) && !now)
        ans += lst ^ x;
      now += y, lst = x;
    }
  };
  For(i, 0, n - 1) For(j, 0, sz(poly[i]) - 1)
    solve(poly[i][j], poly[i][(j + 1) % sz(poly[i])],
      i);
  return ans / 2;
}
