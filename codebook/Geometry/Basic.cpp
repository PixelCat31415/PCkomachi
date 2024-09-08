#define X first
#define Y second
typedef pair<double,double> Pt;
const double eps=1e-9;
Pt operator+(Pt a,Pt b){return Pt(a.X+b.X,a.Y+b.Y);}
Pt operator-(Pt a,Pt b){return Pt(a.X-b.X,a.Y-b.Y);}
Pt operator*(Pt a,double b){return Pt(a.X*b,a.Y*b);}
Pt operator/(Pt a,double b){return Pt(a.X/b,a.Y/b);}
double operator*(Pt a,Pt b){return a.X*b.X+a.Y*b.Y;}
double operator^(Pt a,Pt b){return a.X*b.Y-a.Y*b.X;}
double abs2(Pt a){return a*a;}
double abs(Pt a){return sqrt(a*a);}
int sign(double a){return fabs(a)<eps?0:a>0?1:-1;}
int ori(Pt a,Pt b,Pt c){return sign((b-a)^(c-a));}
bool collinear(Pt a,Pt b,Pt c){return sign((a-c)^(b-c))==0;}
bool btw(Pt a,Pt b,Pt c){return !collinear(a,b,c)?0:sign((a-c)*(b-c))<=0;}//is C between AB
Pt proj(Pt a,Pt b,Pt c){return (b-a)*((c-a)*(b-a)/abs2(b-a));}//ac projection on ab
double dist(Pt a,Pt b,Pt c){return abs((c-a)^(b-a))/abs(b-a);}//distance from C to AB
Pt perp(Pt p1){return Pt(-p1.Y, p1.X);}
struct Line{Pt a,b;};
struct Cir{Pt o;double r;};
struct Arc{Pt o,a,b;};//cross(oa,ob)>=0
