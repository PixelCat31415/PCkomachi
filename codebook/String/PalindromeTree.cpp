struct PalindromicTree {
  struct node {
    int nxt[26], fail, len; // num = depth of fail link
    int cnt, num; // cnt = occur, num = #pal_suffix of this node
    node(int l = 0) : nxt{},fail(0),len(l),cnt(0),num(0) {}
  };
  vector<node> st; vector<int> s; int last, n;
  void init() {
    st.clear(); s.clear(); last = 1; n = 0;
    st.pb(0); st.pb(-1);
    st[0].fail = 1; s.pb(-1);
  }
  int getFail(int x) {
    while (s[n - st[x].len - 1] != s[n]) x = st[x].fail;
    return x;
  }
  void add(int c) {
    s.pb(c -= 'a'); ++n;
    int cur = getFail(last);
    if (!st[cur].nxt[c]) {
      int now = SZ(st);
      st.pb(st[cur].len + 2);
      st[now].fail = st[getFail(st[cur].fail)].nxt[c];
      st[cur].nxt[c] = now;
      st[now].num = st[st[now].fail].num + 1;
    }
    last = st[cur].nxt[c]; ++st[last].cnt;
  }
  void dpcnt() {
    for(int i = SZ(st) - 1; i >= 0; i--){
      auto nd = st[i];
      st[nd.fail].cnt += nd.cnt;
    }
  }
  int size() { return (int)st.size() - 2; }
};
