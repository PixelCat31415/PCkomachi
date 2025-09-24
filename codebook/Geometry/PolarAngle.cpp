// CCW starting from (1, 0) inclusive, w/o tie-breaking
int halfplane(PT p) {
    if (sign(p * p) == 0) return 0;
    return 1 - 2 * (sign(p.y) > 0 || (sign(p.y) == 0 && sign(p.x) > 0));
}  // upper(-1) -> origin(0) -> lower(1)
auto operator<=>(PT a, PT b) {
    int ha = halfplane(a), hb = halfplane(b);
    if (ha != hb) return ha <=> hb;
    return 0 <=> sign(a ^ b);
}  // before c++20: replace <=> with <