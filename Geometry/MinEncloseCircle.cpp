// (FP) needs segment intersect
// p must be nonempty
PT circenter(PT a, PT b, PT c) {
  PT ab = (a + b) / 2, ac = (a + c) / 2;
  return intersect(
    ab, ab + ccw90(b - a),
    ac, ac + ccw90(c - a)
  );
}
Cir min_enclosing(vector<PT> &p) {
  shuffle(p.begin(), p.end(), mt19937(clock()));
  double r = 0;
  PT cent = p[0];
  For(i, 0, sz(p) - 1)
  if (abs2(cent - p[i]) > r) {
    cent = p[i]; r = 0;
    For(j, 0, i - 1)
    if (abs2(cent - p[j]) > r) {
      cent = (p[i] + p[j]) / 2;
      r = abs2(p[j] - cent);
      For(k, 0, j - 1)
      if (abs2(cent - p[k]) > r) {
        cent = circenter(p[i], p[j], p[k]);
        r = abs2(p[k] - cent);
      }
    }
  }
  return {cent, sqrt(r)};
}
