using T = long double;  // int
const double eps=1e-9;  // 1
T operator*(PT a,PT b){return a.x*b.x+a.y*b.y;}
T operator^(PT a,PT b){return a.x*b.y-a.y*b.x;}
T abs2(PT a){return a*a;}
double abs(PT a){return sqrt(a*a);}
int sign(T a){return abs(a)<eps?0:a>0?1:-1;}
int ori(PT a,PT b,PT c){return sign((b-a)^(c-a));}
bool btw(PT a,PT b,PT c){  //is C between AB
  return ori(a,b,c)?0:sign((a-c)*(b-c))<=0;}
PT proj(PT a,PT b,PT c){  //ac projection on ab
  return (b-a)*((c-a)*(b-a)/abs2(b-a));}
double dist(PT a,PT b,PT c){  //distance from C to AB
  return abs((c-a)^(b-a))/abs(b-a);}
PT ccw90(PT p){return PT(-p.y, p.x);}
struct Line{PT a,b;};
struct Cir{PT o;double r;};
