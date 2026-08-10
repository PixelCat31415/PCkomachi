// (int) needs convex hull
// each input needs at least two distinct points
vector<PT> Minkowski(vector<PT> a, vector<PT> b) {
  a = ConvexHull(a), b = ConvexHull(b);
  int n = sz(a), m = sz(b);
  vector<PT> c{a[0] + b[0]}, s1, s2;
  For(i, 0, n - 1)
    s1.push_back(a[(i + 1) % n] - a[i]);
  For(i, 0, m - 1)
    s2.push_back(b[(i + 1) % m] - b[i]);
  for (int p1 = 0, p2 = 0; p1 < n || p2 < m;)
    if (p2 == m || (p1 < n &&
        sign(s1[p1] ^ s2[p2]) >= 0))
      c.push_back(c.back() + s1[p1++]);
    else c.push_back(c.back() + s2[p2++]);
  return ConvexHull(c);
}
