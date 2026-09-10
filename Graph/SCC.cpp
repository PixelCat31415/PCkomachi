int BuildScc(int n, const auto &adj, const auto &radj, auto &scc) { // 0-indexed, returns # of SCCs
  vector<int> stk;
  int cnt = 0;
  auto dfs1 = [&](auto &self, int x) -> void {
    scc[x] = -1;
    for (auto i : adj[x])
      if (scc[i] == 0) self(self, i);
    stk.emplace_back(x);
  };
  auto dfs2 = [&](auto &self, int x) -> void {
    scc[x] = cnt;
    for (auto i : radj[x])
      if (scc[i] == -1) self(self, i);
  };
  fill(scc, scc + n, 0);
  For(i, 0, n - 1) if (scc[i] == 0) dfs1(dfs1, i);
  for (auto i : stk | views::reverse)
    if (scc[i] == -1) dfs2(dfs2, i), cnt++;
  return cnt;
}
// 2-SAT: alloc 2n vertices x0, x1
//   x or y .. x0 -> y1, y0 -> x1
//   forced x .. x0 -> x1
// no sol if scc[x0] == scc[x1]
// else, assign with the one with larger SCC id