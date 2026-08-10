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
PT ccw90(PT p) { return PT(-p.y, p.x); }

//  ori(PT a, PT b, PT c) { // is C to the left of A->B
// change PT::x, y to FP type, replace sign()
// needs PT+-PT, PT*/scalar
const double EPS = 1e-9;
int sign(int a) { return (a > EPS) - (a < EPS); }
double abs2(PT p){ return p * p; }
double abs(PT p){ return sqrt(p * p); }
PT proj(PT a, PT b, PT c){ // C projected to AB
  return a+(b-a)*((c-a)*(b-a)/abs2(b-a));}
double dist(PT a,PT b,PT c){ // distance from C to AB
  return abs((c-a)^(b-a))/abs(b-a);}

// struct Line{ PT a, b; };
// struct Cir{ PT o; double r; };