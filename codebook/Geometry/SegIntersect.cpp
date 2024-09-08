bool seg_sect(Pt p1,Pt p2,Pt p3,Pt p4) {//does p1p2 intersect p3p4
  int a123=ori(p1,p2,p3);
  int a124=ori(p1,p2,p4);
  int a341=ori(p3,p4,p1);
  int a342=ori(p3,p4,p2);
  if(a123==0&&a124==0) return btw(p1,p2,p3)||btw(p1,p2,p4)||btw(p3,p4,p1)||btw(p3,p4,p2);
  else return a123*a124<=0&&a341*a342<=0;
}
Pt intersect(Pt p1, Pt p2, Pt p3, Pt p4) {
  double a123 = (p2 - p1) ^ (p3 - p1);
  double a124 = (p2 - p1) ^ (p4 - p1);
  return (p4 * a123 - p3 * a124) / (a123 - a124); // C^3 / C^2
}
