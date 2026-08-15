// (int) CCW from (1, 0), without length tie-breaking
int halfplane(PT p) {
  if (sign(p * p) == 0) return 0;
  bool upper = sign(p.y) > 0 ||
    (sign(p.y) == 0 && sign(p.x) > 0);
  return 1 - 2 * upper;
}  // upper(-1) -> origin(0) -> lower(1)
strong_ordering polar(PT a, PT b) {
  int ha = halfplane(a), hb = halfplane(b);
  if (ha != hb) return ha <=> hb;
  return 0 <=> sign(a ^ b);
}
