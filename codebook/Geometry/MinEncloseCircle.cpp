Pt circenter(Pt a, Pt b, Pt c) {
  Pt ab = (a + b) / 2, ac = (a + c) / 2;
  return intersect(
    ab, ab + ccw90(b - a),
    ac, ac + ccw90(c - a)
  );
}
Cir min_enclosing(vector<Pt> &p) {
  mt19937 rng(clock());
  shuffle(p.begin(), p.end(), rng);
  double r = 0.0;
  Pt cent = p[0];
  for (int i = 1; i < p.size(); ++i) {
    if (abs2(cent - p[i]) <= r) continue;
    cent = p[i];
    r = 0.0;
    for (int j = 0; j < i; ++j) {
      if (abs2(cent - p[j]) <= r) continue;
      cent = (p[i] + p[j]) / 2;
      r = abs2(p[j] - cent);
      for (int k = 0; k < j; ++k) {
        if (abs2(cent - p[k]) <= r) continue;
        cent = circenter(p[i], p[j], p[k]);
        r = abs2(p[k] - cent);
      }
    }
  }
  return {cent, sqrt(r)};
}