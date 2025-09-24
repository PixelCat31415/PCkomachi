#define sz(x) ((int)x.size())
vector<PT> ConvexHull(vector<PT> pt) {
  int n = sz(pt);
  sort(pt.begin(), pt.end(), [&](PT a, PT b) {return a.x == b.x ? a.y < b.y : a.x < b.x;});
  vector<PT> ans = {pt[0]};
  rep(t, 2) {
    int m = sz(ans);
    rep1(i, n - 1) {
      while (sz(ans) > m && ori(ans[sz(ans) - 2], ans.back(), pt[i]) <= 0)
        ans.pop_back();
      ans.pb(pt[i]);
    }
    reverse(pt.begin(), pt.end());
  }
  if (sz(ans) > 1) ans.pop_back();
  return ans;
}