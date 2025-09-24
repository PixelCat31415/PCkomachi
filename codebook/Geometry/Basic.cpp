using T = long double;  // int
const double eps=1e-9;  // 1
T operator*(Pt a,Pt b){return a.x*b.x+a.y*b.y;}
T operator^(Pt a,Pt b){return a.x*b.y-a.y*b.x;}
T abs2(Pt a){return a*a;}
double abs(Pt a){return sqrt(a*a);}
int sign(T a){return abs(a)<eps?0:a>0?1:-1;}
int ori(Pt a,Pt b,Pt c){return sign((b-a)^(c-a));}
bool collinear(Pt a,Pt b,Pt c){return sign((a-c)^(b-c))==0;}
bool btw(Pt a,Pt b,Pt c){return !collinear(a,b,c)?0:sign((a-c)*(b-c))<=0;}//is C between AB
Pt proj(Pt a,Pt b,Pt c){return (b-a)*((c-a)*(b-a)/abs2(b-a));}//ac projection on ab
double dist(Pt a,Pt b,Pt c){return abs((c-a)^(b-a))/abs(b-a);}//distance from C to AB
Pt ccw90(Pt p1){return Pt(-p1.y, p1.x);}
struct Line{Pt a,b;};
struct Cir{Pt o;double r;};
