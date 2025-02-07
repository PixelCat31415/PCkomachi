// sum of val over (x, y, z) <= (x', y', z')
struct Point { array<int, 3> pos; ll val, sum; };
void partial_order_sum(vector<Point> &v) {
  sort(v.begin(), v.end(),
    [](auto a, auto b){return a.pos < b.pos;});
  for(auto &i:v) i.sum = i.val;
  BIT<ll> bit(MAXZ + 10);
  auto dfs = [&](auto _dfs, int l, int r) {
    if(l == r) return;
    int m = (l + r) / 2;
    _dfs(_dfs, l, m);
    _dfs(_dfs, m + 1, r);
    auto cmpy = [](auto a, auto b){return a.pos[1] < b.pos[1];};
    sort(v.begin() + l, v.begin() + m + 1, cmpy);
    sort(v.begin() + m + 1, v.begin() + r + 1, cmpy);
    int i = l;
    for(int j = m + 1; j <= r; j++) {
      while(i <= m && v[i].pos[1] <= v[j].pos[1]) {
        bit.add(v[i].pos[2], v[i].val); i++;
      }
      v[j].sum += bit.query(v[j].pos[2]);
    }
    while(--i >= l) bit.add(v[i].pos[2], -v[i].val);
  };
  dfs(dfs, 0, (int)v.size() - 1);
}