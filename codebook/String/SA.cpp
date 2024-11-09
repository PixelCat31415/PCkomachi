#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define ROF(i, a, b) for(int i = a; i >= b; i--)
int sa[N], tmp[2][N], c[N], rk[N], lcp[N];
void buildSA(string s) {
  int *x = tmp[0], *y = tmp[1], m = 256, n = (int)s.size();
  FOR(i, 0, m - 1) c[i] = 0;
  FOR(i, 0, n - 1) c[x[i] = s[i]]++;
  FOR(i, 1, m - 1) c[i] += c[i - 1];
  ROF(i, n - 1, 0) sa[--c[x[i]]] = i;
  for (int k = 1; k < n; k <<= 1) {
    FOR(i, 0, m - 1) c[i] = 0;
    FOR(i, 0, n - 1) c[x[i]]++;
    FOR(i, 1, m - 1) c[i] += c[i - 1];
    int p = 0;
    FOR(i, n - k, n - 1) y[p++] = i;
    FOR(i, 0, n - 1) if(sa[i] >= k) y[p++] = sa[i] - k;
    ROF(i, n - 1, 0) sa[--c[x[y[i]]]] = y[i];
    y[sa[0]] = p = 0;
    FOR(i, 1, n - 1) {
      int a = sa[i], b = sa[i - 1];
      if (!(x[a] == x[b] && a + k < n && b + k < n && x[a + k] == x[b + k])) p++;
      y[sa[i]] = p;
    }
    if (n == p + 1) break;
    swap(x, y), m = p + 1;
  }
}
void buildLCP(string s) {
  // lcp[i] = LCP(sa[i - 1], sa[i])
  // lcp(i, j) = min(lcp[rk[i] + 1], lcp[rk[i] + 2], ..., lcp[rk[j]])
  int n = (int)s.size(), val = 0;
  FOR(i, 0, n - 1) rk[sa[i]] = i;
  FOR(i, 0, n - 1) {
    if (!rk[i]) lcp[rk[i]] = 0;
    else {
      if (val) val--;
      int p = sa[rk[i] - 1];
      while (val + i < n && val + p < n && s[val + i] == s[val + p]) val++;
      lcp[rk[i]] = val;
    }
  }
}