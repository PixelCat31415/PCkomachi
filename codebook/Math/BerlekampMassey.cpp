const int MOD=998244353;
vector <ll> BerlekampMassey(vector <ll> a) {
  // find min |c| such that a_n = sum c_j * a_{n - j - 1}, 0-based
  // O(N^2), if |c| = k, |a| >= 2k sure correct
  auto f = [&](vector<ll> v, ll c) {
    for (ll &x : v) x = x * c % MOD;
    return v;
  };
  vector <ll> c, best;
  int pos = 0, n = a.size();
  for (int i = 0; i < n; ++i) {
    ll error = a[i];
    for (int j = 0; j < c.size(); ++j) error = ((error - c[j] * a[i - 1 - j]) % MOD + MOD) % MOD;
    if (error == 0) continue;
    ll inve = inv(error, MOD);
    if (c.empty()) {
      c.resize(i + 1);
      pos = i;
      best.pb(inve);
    } else {
      vector <ll> fix = f(best, error);
      fix.insert(fix.begin(), i - pos - 1, 0);
      if (fix.size() >= c.size()) {
        best = f(c, inve > 0 ? MOD-inve : 0);
        best.insert(best.begin(), inve);
        pos = i;
        c.resize(fix.size());
      }
      for (int j = 0; j < fix.size(); ++j) c[j] = (c[j] + fix[j]) % MOD;
    }
  }
  return c;
}
