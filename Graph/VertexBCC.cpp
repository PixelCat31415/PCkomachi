struct BCC{ // 0-based, allow multi edges but not allow loops
  int n, m, cnt = 0;
  // n:|V|, m:|E|, cnt:#bcc
  // bcc i : vertices bcc_v[i] and edges bcc_e[i]
  vector<vector<int>> bcc_v, bcc_e;
  vector<vector<pii>> g; // original graph
  vector<pii> edges; // 0-based
  BCC(int _n, vector<pii> _edges):
    n(_n), m(SZ(_edges)), g(_n), edges(_edges){
      for(int i = 0; i < m; i++){
        auto [u, v] = edges[i];
        g[u].pb(pii(v, i)); g[v].pb(pii(u, i));
      }
    }
  void make_bcc(){ bcc_v.pb(); bcc_e.pb(); cnt++; }
  // modify these if you need more information
  void add_v(int v){ bcc_v.back().pb(v); }
  void add_e(int e){ bcc_e.back().pb(e); }
  void build(){
    vector<int> in(n, -1), low(n, -1), stk;
    vector<vector<int>> up(n);
    int ts = 0;
    auto _dfs = [&](auto dfs, int now, int par, int pe) -> void{
      if(pe != -1) up[now].pb(pe);
      in[now] = low[now] = ts++;
      stk.pb(now);
      for(auto [v, e] : g[now]){
        if(e == pe) continue;
        if(in[v] != -1){
          if(in[v] < in[now]) up[now].pb(e);
          low[now] = min(low[now], in[v]);
          continue;
        }
        dfs(dfs, v, now, e);
        low[now] = min(low[now], low[v]);
      }
      if((now != par && low[now] >= in[par]) || (now == par && SZ(g[now]) == 0)){
        make_bcc();
        for(int v = stk.back();; v = stk.back()){
          stk.pop_back(), add_v(v);
          for(int e : up[v]) add_e(e);
          if(v == now) break;
        }
        if(now != par) add_v(par);
      }
    };
    for(int i = 0; i < n; i++)
      if(in[i] == -1) _dfs(_dfs, i, i, -1);
  }
};
