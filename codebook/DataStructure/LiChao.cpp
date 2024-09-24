//C is range of x
//INF is big enough integer
struct Line {
  ll m,k;
  Line(ll _m=0,ll _k=0): m(_m),k(_k){}
  ll val(ll x){return m*x+k;}
};
struct LiChaoTree { //max y value
  Line st[C<<2];
  void init(int l,int r,int id) {
    st[id]=Line(0,0);
    if(l==r) return;
    int mid=(l+r)/2;
    init(l,mid,id<<1);
    init(mid+1,r,id<<1|1);
  }
  void upd(int l,int r,Line seg,int id) {
    if(l==r) {
      if(seg.val(l)>st[id].val(l)) st[id]=seg;
      return;
    }
    int mid=(l+r)/2;
    if(st[id].m>seg.m) swap(st[id],seg);
    if(st[id].val(mid)<seg.val(mid)) {
      swap(st[id],seg);
      upd(l,mid,seg,id<<1);
    } else upd(mid+1,r,seg,id<<1|1);
  }
  ll qry(int l,int r,ll x,int id) {
    if(l==r) return st[id].val(x);
    int mid=(l+r)/2;
    if(x<=mid) return max(qry(l,mid,x,id<<1),st[id].val(x));
    else return max(qry(mid+1,r,x,id<<1|1),st[id].val(x));
  }
};
