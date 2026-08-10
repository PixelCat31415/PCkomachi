struct PT { int x, y; };
PT operator+(PT p1, PT p2)
{ return PT{p1.x + p2.x, p1.y + p2.y}; }
PT operator-(PT p1, PT p2)
{ return PT{p1.x - p2.x, p1.y - p2.y}; }
int operator*(PT p1, PT p2)
{ return p1.x * p2.x + p1.y * p2.y; }
int operator^(PT p1, PT p2)
{ return p1.x * p2.y - p1.y * p2.x; }
int sign(int a) { return (a > 0) - (a < 0); }
int ori(PT a, PT b, PT c) { // is C to the left of A->B
  return sign((b-a)^(c-a)); }
bool btw(PT a, PT b, PT c) { // is C between AB
  return !ori(a, b, c) && sign((a-c)*(b-c)) <= 0; }
