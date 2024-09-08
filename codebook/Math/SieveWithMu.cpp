const int N=1e6+1;
int lpf[N],mu[N];
vector<int> pr;
void sieve_with_mu() {
  mu[1]=1;
  for(int i=2;i<N;i++) {
    if(lpf[i]==0) {
      lpf[i]=i,mu[i]=-1;
      pr.push_back(i);
    }
    for(int j=0;j<(int)pr.size()&&pr[j]<=lpf[i]&&i*pr[j]<N;j++) {
      lpf[i*pr[j]]=pr[j];
      mu[i*pr[j]]=mu[i]*(pr[j]==lpf[i]?0:-1);
    }
  }
}
