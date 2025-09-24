using T = long double;  // int
const double eps=1e-9;  // 1
T operator*(Pt a,Pt b){return a.x*b.x+a.y*b.y;}
T operator^(Pt a,Pt b){return a.x*b.y-a.y*b.x;}
T abs2(Pt a){return a*a;}
double abs(Pt a){return sqrt(a*a);}
int sign(T a){return abs(a)<eps?0:a>0?1:-1;}
int ori(Pt a,Pt b,Pt c){return sign((b-a)^(c-a));}
bool btw(Pt a,Pt b,Pt c){  //is C between AB
  return ori(a,b,c)?0:sign((a-c)*(b-c))<=0;}
Pt proj(Pt a,Pt b,Pt c){  //ac projection on ab
  return (b-a)*((c-a)*(b-a)/abs2(b-a));}
double dist(Pt a,Pt b,Pt c){  //distance from C to AB
  return abs((c-a)^(b-a))/abs(b-a);}
Pt ccw90(Pt p){return Pt(-p.y, p.x);}
struct Line{Pt a,b;};
struct Cir{Pt o;double r;};
