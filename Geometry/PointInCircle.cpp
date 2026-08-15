// (int) p1, p2, p3 must be in CCW order
// test if p4 strictly in circumcircle of p1p2p3
bool InCir(PT p1, PT p2, PT p3, PT p4) {
  p1 = p1 - p4; p2 = p2 - p4; p3 = p3 - p4;
  ll l1 = p1 * p1, l2 = p2 * p2, l3 = p3 * p3;
  i128 det = (i128)l1 * (p2 ^ p3)
           + (i128)l2 * (p3 ^ p1)
           + (i128)l3 * (p1 ^ p2);
  return det > 0;
}
