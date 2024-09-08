//N: number of branches
//M: range of SegTree
//SZ: size of segTree, need to be about C*4+NlogC
int sz=0,root[N];
struct Node {
  int l,r,val;
  Node(int _l=-1,int _r=-1,int _val=0): l(_l),r(_r),val(_val){}
} st[SZ];

void build(int l,int r,int id) {
  if(l==r) st[id]=Node();
  else {
    int mid=l+r>>1;
    st[id]=Node(sz+1,sz+2,0);
    sz+=2;
    build(l,mid,st[id].l);
    build(mid+1,r,st[id].r);
  }
}
void upd(int l,int r,int pos,int from,int id) {
  if(l==r) {
    st[id]=Node(-1,-1,st[from].val+1);
    return;
  } else {
    int mid=l+r>>1;
    if(pos<=mid) {
      sz++;
      st[id]=Node(sz,st[from].r,0);
      upd(l,mid,pos,st[from].l,st[id].l);
    } else {
      sz++;
      st[id]=Node(st[from].l,sz,0);
      upd(mid+1,r,pos,st[from].r,st[id].r);
    }
    st[id].val=st[st[id].l].val+st[st[id].r].val;
  }
}
int qry(int l,int r,int k,int x,int y)//cnt(x)-cnt(y), finding k-th smallest
{
  if(l==r) return l;
  else {
    int mid=l+r>>1;
    int lx=st[x].l,ly=st[y].l;
    if(st[lx].val-st[ly].val>=k) return qry(l,mid,k,lx,ly);
    else return qry(mid+1,r,k-(st[lx].val-st[ly].val),st[x].r,st[y].r);
  }
}
