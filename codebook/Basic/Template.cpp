template<typename T> void _do(T x){cerr<<x<<"\n";}
template<typename T,typename ...U> void _do(T x,U ...y){cerr<<x<<", ";_do(y...);}
#define dbg(...) cerr<<#__VA_ARGS__<<" = ";_do(__VA_ARGS__);
#define uni(c) c.resize(distance(c.begin(),unique(c.begin(),c.end())))
#define unisort(c) sort(c.begin(),c.end()),uni(c)
auto SEED = chrono::steady_clock::now().time_since_epoch().count();
mt19937 rng(SEED);
// cpp $1 -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum | cut -c-6
