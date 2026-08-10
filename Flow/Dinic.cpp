template <typename T> // 0-based, O(V^2E), unit flow: O(min(V^{2/3}E, E^{3/2})), bipartite matching: O(sqrt(V)E)
struct Dinic { // 0-based
  const T INF = numeric_limits<T>::max() / 2;
  struct edge { int to, rev; T cap, flow; };
  int n, s, t;
  vector <vector <edge>> g;
  vector <int> dis, cur;
  T dfs(int u, T cap) { // SCOPE HASH
    if (u == t || !cap) return cap;
    for (int &i = cur[u]; i < (int)g[u].size(); ++i) {
      edge &e = g[u][i];
      if (dis[e.to] == dis[u] + 1 && e.flow != e.cap) {
        T df = dfs(e.to, min(e.cap - e.flow, cap));
        if (df) {
          e.flow += df;
          g[e.to][e.rev].flow -= df;
          return df;
    } } }
    dis[u] = -1;
    return 0;
  }
  bool bfs() { // SCOPE HASH
    fill(all(dis), -1);
    queue<int> q;
    q.push(s); dis[s] = 0;
    while (!q.empty()) {
      int v = q.front(); q.pop();
      for (auto &u : g[v])
        if (dis[u.to] == -1 && u.flow != u.cap) {
          q.push(u.to);
          dis[u.to] = dis[v] + 1;
        }
    }
    return dis[t] != -1;
  }
  T solve(int _s, int _t) { // SCOPE HASH
    s = _s; t = _t;
    T flow = 0, df;
    while (bfs()) {
      fill(all(cur), 0);
      while ((df = dfs(s, INF))) flow += df;
    }
    return flow;
  }
  void reset() {
    for (int i = 0; i < n; ++i)
      for (auto &j : g[i]) j.flow = 0;
  }
  void add_edge(int u, int v, T cap) {
    g[u].pb(edge{v, (int)g[v].size(), cap, 0});
    g[v].pb(edge{u, (int)g[u].size() - 1, 0, 0});
	//change g[v] to cap for undirected graphs
  }
  Dinic (int _n) : n(_n), g(n), dis(n), cur(n) {}
};
