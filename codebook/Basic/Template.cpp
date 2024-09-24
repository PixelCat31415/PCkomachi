#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
template<typename T> void _do(T x){cerr<<x<<"\n";}
template<typename T,typename ...U> void _do(T x,U ...y){cerr<<x<<", ";_do(y...);}
#define dbg(...) cerr<<#__VA_ARGS__<<" = ";_do(__VA_ARGS__);
#define MottoHayaku ios::sync_with_stdio(false);cin.tie(0);
#define rep(i,n) for(int i=0;i<n;i++)
#define rep1(i,n) for(int i=1;i<=n;i++)
#define F first
#define S second
#define pb push_back
#define uni(c) c.resize(distance(c.begin(),unique(c.begin(),c.end())))
#define unisort(c) sort(c.begin(),c.end()),uni(c)
#define ALL(a) a.begin(),a.end()
#define SZ(a) ((int)a.size())
