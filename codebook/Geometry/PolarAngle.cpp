bool upper(Pt p) {
  return p.Y > 0 || (p.Y == 0 && p.X >= 0);
}
int polarOri(Pt p1, Pt p2) {  // p1 (-1 <)(0 =)(1 >) p2
  if(upper(p1) != upper(p2)) return upper(p1) ? -1 : 1;
  return -sign(p1 ^ p2);
}
bool cmpPolar(Pt p1, Pt p2) {  // 0...2pi CCW
  return polarOri(p1, p2) < 0;
}