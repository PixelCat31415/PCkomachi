// (int)
// requires sz(pt) >= 2 & distinct points
// points on edges are excluded
vector<PT> ConvexHull(vector<PT> pt) {
  int n = sz(pt);
  sort(iter(pt));
  vector<PT> ans{pt[0]};
  For(t, 0, 1) {
    int m = sz(ans);
    For(i, 1, n - 1) {
      while (sz(ans) > m && ori(ans[sz(ans) - 2],
        ans.back(), pt[i]) <= 0) ans.pop_back();
      ans.push_back(pt[i]);
    }
    reverse(iter(pt));
  }
  if (sz(ans) > 1) ans.pop_back();
  return ans;
}
