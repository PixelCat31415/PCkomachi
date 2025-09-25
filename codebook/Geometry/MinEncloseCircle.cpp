Pt circenter(Pt a, Pt b, Pt c) {
  Pt ab = (a + b) / 2, ac = (a + c) / 2;
  return intersect(
    ab, ab + ccw90(b - a),
    ac, ac + ccw90(c - a)
  );
}
Cir min_enclosing(vector<Pt> &p) {
  shuffle(p.begin(), p.end(), mt19937(clock()));
  double r = 0;
  Pt cent = p[0];
  rep(i, p.size()) if (abs2(cent - p[i]) > r) {
    cent = p[i]; r = 0;
    rep(j, i) if (abs2(cent - p[j]) > r) {
      cent = (p[i] + p[j]) / 2;
      r = abs2(p[j] - cent);
      rep(k, j) if (abs2(cent - p[k]) > r) {
        cent = circenter(p[i], p[j], p[k]);
        r = abs2(p[k] - cent);
      }
    }
  }
  return {cent, sqrt(r)};
}