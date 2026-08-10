// (int)
// p1, p2, p3 must be in CCW order
// is p4 strictly in circumcircle of p1p2p3
ll sq(ll x) { return x * x; }
bool in_cc(PT p1, PT p2, PT p3, PT p4) {
  ll u11 = p1.x - p4.x; ll u12 = p1.y - p4.y;
  ll u21 = p2.x - p4.x; ll u22 = p2.y - p4.y;
  ll u31 = p3.x - p4.x; ll u32 = p3.y - p4.y;
  ll u13 = sq(p1.x) - sq(p4.x) + sq(p1.y) - sq(p4.y);
  ll u23 = sq(p2.x) - sq(p4.x) + sq(p2.y) - sq(p4.y);
  ll u33 = sq(p3.x) - sq(p4.x) + sq(p3.y) - sq(p4.y);
  i128 det =
    - (i128)u13 * u22 * u31 + (i128)u12 * u23 * u31
    + (i128)u13 * u21 * u32 - (i128)u11 * u23 * u32
    - (i128)u12 * u21 * u33 + (i128)u11 * u22 * u33;
  return det > 0;
}
