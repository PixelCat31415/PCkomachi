/*
Each matroid needs:
vector<bool> build_X(vector<bool> &I)
void build_exchange_graph(vector<vector<int> > &adj,vector<bool> &I)
exchange graph has to be opposite. i.e. one i->j one j->i from two matroids
*/
template <typename M1, typename M2>
struct MatroidIntersection {
  M1 m1;
  M2 m2;
  MatroidIntersection (M1 _m1, M2 _m2) : m1(_m1), m2(_m2) {}
  /* 1. build X1, X2
     2. If e \in X1 and e \in X2, add e
     3. Else build exchange graph
        m1 -> add edge from I to E \ I
        m2 -> add edge from E \ I to I
        weight: I -> w, E \ I -> -w
     4. find a minimum path (weight, number) from X1 to X2 (use bfs or SPFA) */
  vector <vector <int>> adj;
  vector <int> bfs(vector <bool> &X1, vector <bool> &X2) {
    int n = X1.size();
    queue <int> q;
    vector <int> dis(n, -1), rt(n, -1);
    for (int i = 0; i < n; ++i) if (X1[i])
      q.push(i), dis[i] = 0;
    while (!q.empty()) {
      int v = q.front(); q.pop();
      for (int u : adj[v]) if (dis[u] == -1) {
        dis[u] = dis[v] + 1, rt[u] = v;
        q.push(u);
      }
    }
    pair <int, int> mn = make_pair(1 << 30, -1);
    for (int i = 0; i < n; ++i) if (X2[i] && dis[i] != -1)
      mn = min(mn, make_pair(dis[i], i));
    int now = mn.second;
    if (now == -1)
      return {};
    vector <int> path = {now};
    while (rt[now] != -1) {
      now = rt[now], path.push_back(now);
    }
    reverse(path.begin(), path.end());
    return path;
  }
  vector <bool> solve(int n) {
    vector <bool> I(n, false);
    while (true) {
      vector <bool> X1 = m1.build_X(I), X2 = m2.build_X(I);
      if (count(X1.begin(), X1.end(), 0) == n || count(X2.begin(), X2.end(), 0) == n)
        break;
      int add = -1;
      for (int i = 0; i < n; ++i) if (X1[i] && X2[i]) {
        add = i;
        break;
      }
      if (add != -1) {
        I[add] = true;
        continue;
      }
      adj.assign(n, vector <int>());
      m1.build_exchange_graph(adj, I);
      m2.build_exchange_graph(adj, I);
      vector <int> path = bfs(X1, X2);
      if (path.empty())
        break;
      for (int i : path)
        I[i] = !I[i];
    }
    return I;
  }
  vector <int> SPFA(vector <bool> &X1, vector <bool> &X2, vector <bool> &I, vector <int> &weight) {
    int n = X1.size();
    queue <int> q;
    vector <pair <int, int>> dis(n, make_pair(1 << 30, -1));
    vector <int> rt(n, -1);
    vector <bool> vis(n, false);
    for (int i = 0; i < n; ++i) if (X1[i])
      q.push(i), dis[i] = make_pair(-weight[i], 0), vis[i] = true;
    while (!q.empty()) {
      int v = q.front(); q.pop();
      vis[v] = false;
      for (int u : adj[v]) {
        pair <int, int> nxt = make_pair(dis[v].first + (I[u] ? weight[u] : -weight[u]), dis[v].second + 1);
        if (dis[u] > nxt) {
          dis[u] = nxt, rt[u] = v;
          if (!vis[u])
            q.push(u), vis[u] = true;
        }
      }
    }
    pair <pair <int, int>, int> mn = make_pair(make_pair(1 << 30, -1), -1);
    for (int i = 0; i < n; ++i) if (X2[i])
      mn = min(mn, make_pair(dis[i], i));
    int now = mn.second;
    if (now == -1)
      return {};
    vector <int> path = {now};
    while (rt[now] != -1) {
      now = rt[now], path.push_back(now);
    }
    reverse(path.begin(), path.end());
    return path;
  }
  vector <bool> solve_max_weight(vector <int> weight) {
    int n = weight.size();
    vector <bool> I(n, false);
    while (true) {
      vector <bool> X1 = m1.build_X(I), X2 = m2.build_X(I);
      if (count(X1.begin(), X1.end(), 0) == n || count(X2.begin(), X2.end(), 0) == n)
        break;
      adj.assign(n, vector <int>());
      m1.build_exchange_graph(adj, I);
      m2.build_exchange_graph(adj, I);
      vector <int> path = SPFA(X1, X2, I, weight);
      if (path.empty())
        break;
      for (int i : path)
        I[i] = !I[i];
    }
    return I;
  }
};
