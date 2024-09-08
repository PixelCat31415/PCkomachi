ll fpow(ll a,ll b,ll m) {
  if(!b) return 1;
  ll ret=1;
  for(;b;b>>=1,a=a*a%m) if(b&1) ret=ret*a%m;
  return ret;
}
ll inv(ll a,ll m) {return fpow(a,m-2,m);}
