//N is number of vertices
struct DisjointSetUnion {
  int par[N],sz[N],ccnt=0;
  stack<pair<int*,int> > st_sz,st_par;
  void init(int n) {
    while(!st_sz.empty()) st_sz.pop();
    while(!st_par.empty()) st_par.pop();
    ccnt=n;
    for(int i=0;i<n;i++) {
      par[i]=i,sz[i]=1;
    }
  }
  int fp(int x) {
    while(x!=par[x]) x=par[x];
    return x;
  }
  bool unite(int x,int y) {
    x=fp(x),y=fp(y);
    if(x==y) return 0;
    if(sz[x]<sz[y]) swap(x,y);
    st_sz.push(make_pair(&sz[x],sz[x]));
    st_par.push(make_pair(&par[y],par[y]));
    ccnt--;
    sz[x]+=sz[y];
    par[y]=x;
    return 1;
  }
  void undo() {
    pair<int*,int> p_par=st_par.top(),p_sz=st_sz.top();
    st_par.pop();
    st_sz.pop();
    *p_par.first=p_par.second;
    *p_sz.first=p_sz.second;
    ccnt++;
  }
};
