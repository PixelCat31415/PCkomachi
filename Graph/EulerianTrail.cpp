// undirected, 0-based
// returns first vertex, or -1 if no solution
// vector<pii> adj[MAXN + 10];  // to, eid
int EulerianTrail(int n, int m, vector<int> &trail) {
  if (m == 0) return 0;
  vector<int> vis(m, 0), cur(n, 0);
  auto dfs = [&](auto self, int v) -> void {
    for (int &i = cur[v]; i < sz(adj[v]);) {
      auto [to, eid] = adj[v][i++];
      if (vis[eid]++) continue;
      self(self, to);
      trail.emplace_back(eid);
    }
  };
  int c = 0, s = 0;
  while (sz(adj[s]) == 0) s++;
  For(i, 1, n - 1) if (sz(adj[i]) & 1) c++, s = i;
  if (c > 2) return -1;
  dfs(dfs, s); reverse(iter(trail));
  return sz(trail) == m ? s : -1;
}
