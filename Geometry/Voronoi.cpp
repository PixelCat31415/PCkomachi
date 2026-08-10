// (int) needs delaunay triangulation
// all coord. is even, you may want to call halfPlaneInter after then
vector<vector<Line>> vec;
void build_voronoi_line(int n, PT *arr) {
  tool.init(n, arr); // Delaunay
  vec.clear(), vec.resize(n);
  for (int i = 0; i < n; ++i)
    for (auto e : tool.head[i]) {
      int u = tool.oidx[i], v = tool.oidx[e.id];
      PT m{(arr[v].x + arr[u].x) / 2,
        (arr[v].y + arr[u].y) / 2};
      PT d = ccw90(arr[v] - arr[u]);
      vec[u].push_back({m, m + d});
    }
}
