// depends on polar angle
auto area_pair(Line a, Line b) {
  return make_pair((a.b - a.a) ^ (b.a - a.a),
    (a.b - a.a) ^ (b.b - a.a));
}
bool isin(Line l0, Line l1, Line l2) {
  // Check inter(l1, l2) strictly in l0
  auto [a02X, a02Y] = area_pair(l0, l2);
  auto [a12X, a12Y] = area_pair(l1, l2);
  if (a12X < a12Y) a12X *= -1, a12Y *= -1;
  return (__int128) a02Y * a12X > (__int128) a02X * a12Y;
}
/* [solution exists] <=> [result.size() > 2] */
/* --^-- Line.a --^-- Line.b --^-- */
#define sz(x) ((int)x.size())
vector<Line> HalfPlaneInter(vector<Line> arr) {
  sort(arr.begin(), arr.end(), [&](Line a, Line b) {
    PT p1 = a.b - a.a, p2 = b.b - b.a;
    if ((p1 <=> p2) != 0) return p1 < p2;
    return ori(a.a, a.b, b.b) < 0;
  });
  deque<Line> dq(1, arr[0]);
  auto pop_back = [&](int t, Line p) {
    while (sz(dq) >= t && !isin(p, dq[sz(dq) - 2], dq.back()))
      dq.pop_back();
  };
  auto pop_front = [&](int t, Line p) {
    while (sz(dq) >= t && !isin(p, dq[0], dq[1]))
      dq.pop_front();
  };
  for (auto p : arr)
    if (((dq.back().b - dq.back().a) <=> (p.b - p.a)) != 0)
      pop_back(2, p), pop_front(2, p), dq.pb(p);
  pop_back(3, dq[0]), pop_front(3, dq.back());
  return vector<Line>(dq.begin(), dq.end());
}