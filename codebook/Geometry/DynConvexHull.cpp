struct DynamicConvexHull {
  struct UpCmp {
    bool operator()(const PT a,const PT b) const {
      if(a.x==b.x) return a.y<b.y;
      return a.x<b.x;
    }
  };
  struct DownCmp {
    bool operator()(const PT a,const PT b) const {
      if (a.x==b.x) return a.y>b.y;
	    return a.x>b.x;
    }
  };
  template <typename T>
  struct Hull {
    set<PT,T> hull;
    bool chk(PT i,PT j,PT k){return ((k-i)^(j-i))>0;}
    void insert(PT x) {
      if(inside(x)) return;
      hull.insert(x);
      auto it=hull.lower_bound(x);
      if(next(it)!=hull.end()) {
        for(auto it2=next(it);next(it2)!=hull.end();++it2) {
          if(chk(x,*it2,*next(it2))) break;
          hull.erase(it2);
          it2=hull.lower_bound(x);
        }
      }
      it=hull.lower_bound(x);
      if(it!=hull.begin()) {
        for(auto it2=prev(it);it2!=hull.begin();--it2) {
          if(chk(*prev(it2),*it2,x)) break;
          hull.erase(it2);
          it2=hull.lower_bound(x);
          if(it2==hull.begin()) break;
        }
      }
    }
    bool inside(PT x) {
      if(hull.lower_bound(x)!=hull.end()&&*hull.lower_bound(x)==x)
        return true;
      auto it=hull.lower_bound(x);
      bool ans=false;
      if(it!=hull.begin()&&it!=hull.end()) {
        ans=!chk(*prev(it),x,*it);
      }
      return ans;
    }
  };
  Hull<UpCmp> up;
  Hull<DownCmp> down;
  void insert(PT x){up.insert(x),down.insert(x);}
  bool inside(PT x){return up.inside(x)&&down.inside(x);}
};