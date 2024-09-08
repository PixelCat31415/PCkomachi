template <typename F, typename C>
struct MinCostCirculation {
  struct ep { int to; F flow; C cost; };
  int n; vector<int> vis; int visc;
  vector<int> fa, fae; vector<vector<int>> g;
  vector<ep> e; vector<C> pi;
  MinCostCirculation(int n_) : n(n_), vis(n), visc(0), g(n), pi(n) {}
  void add_edge(int u, int v, F fl, C cs) {
    g[u].emplace_back((int)e.size());
    e.emplace_back(v, fl, cs);
    g[v].emplace_back((int)e.size());
    e.emplace_back(u, 0, -cs);
  }
  C phi(int x) {
    if (fa[x] == -1) return 0;
    if (vis[x] == visc) return pi[x];
    vis[x] = visc;
    return pi[x] = phi(fa[x]) - e[fae[x]].cost;
  }
  int lca(int u, int v) {
    for (; u != -1 || v != -1; swap(u, v)) if (u != -1) {
      if (vis[u] == visc) return u;
      vis[u] = visc; u = fa[u];
    }
    return -1;
  }
  void pushflow(int x, C &cost) {
    int v = e[x ^ 1].to, u = e[x].to; ++visc;
    if (int w = lca(u, v); w == -1) {
      while (v != -1)
        swap(x ^= 1, fae[v]), swap(u, fa[v]), swap(u, v);
    } else {
      int z = u, dir = 0; F f = e[x].flow;
      vector<int> cyc = {x};
      for (int d : {0, 1})
        for (int i = (d ? u : v); i != w; i = fa[i]) {
          cyc.push_back(fae[i] ^ d);
          if (chmin(f, e[fae[i] ^ d].flow)) z = i, dir = d;
        }
      for (int i : cyc) {
        e[i].flow -= f; e[i ^ 1].flow += f;
        cost += f * e[i].cost;
      }
      if (dir) x ^= 1, swap(u, v);
      while (u != z)
        swap(x ^= 1, fae[v]), swap(u, fa[v]), swap(u, v);
    }
  }
  void dfs(int u) {
    vis[u] = visc;
    for (int i : g[u])
      if (int v = e[i].to; vis[v] != visc and e[i].flow)
        fa[v] = u, fae[v] = i, dfs(v);
  }
  C simplex() {
    fa.assign(g.size(), -1); fae.assign(g.size(), -1);
    C cost = 0; ++visc; dfs(0);
    for (int fail = 0; fail < ssize(e); )
      for (int i = 0; i < ssize(e); i++)
        if (e[i].flow and e[i].cost < phi(e[i ^ 1].to) - phi(e[i].to))
          fail = 0, pushflow(i, cost), ++visc;
        else ++fail;
    return cost;
  }
};
