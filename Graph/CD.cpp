struct CenDecomp {
  int n, mxdep;
  vector<int> par, dep;
  CenDecomp(int _n, const auto &adj): n(_n), mxdep(0), par(n, -1), dep(n, -1) {
    vector<pii> szs(n); int ns = 0;
    auto getsz = [&](auto &self, int v, int p) -> int {
      int sz = 1;
      for (auto i : adj[v]) if (i != p && dep[i] == -1)
        sz += self(self, i, v);
      szs[ns++] = {sz, v};
      return sz;
    };
    auto dfs = [&](auto &self, int v, int p, int d) -> void {
      int tot = getsz(getsz, v, v), j = 0;
      while (szs[j].F <= tot / 2) j++;
      v = szs[j].S; ns = 0;
      par[v] = p; dep[v] = d;
      mxdep = max(mxdep, d + 1);
      for (auto i : adj[v]) if (dep[i] == -1)
        self(self, i, v, d + 1);
    };
    dfs(dfs, 0, -1, 0);
  }  // adj could be vector<vector> or vector[]
};  // 0-indexed nodes, par[root] = -1, dep[root] = 0
