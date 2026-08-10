int BSGS(int s, int x, int y, int m) { // SCOPE HASH
  constexpr int kStep = 32000;
  unordered_map<int, int> p;
  int b = 1;
  for (int i = 0; i < kStep; ++i) {
    p[y] = i;
    y = 1ll * y * x % m;
    b = 1ll * b * x % m;
  }
  for (int i = 0; i < m + 10; i += kStep) {
    s = 1ll * s * b % m;
    if (p.find(s) != p.end()) return i + kStep - p[s];
  }
  return -1; // returns: j where s*(x^j) = y (mod m)
}
int DiscreteLog(int x, int y, int m) { // SCOPE HASH
  if (m == 1) return 0;
  int s = 1;
  for (int i = 0; i < 100; ++i) {
    if (s == y) return i;
    s = 1ll * s * x % m;
  }
  if (s == y) return 100;
  int p = 100 + BSGS(s, x, y, m);
  if (fpow(x, p, m) != y) return -1;
  return p; //returns: x^p = y (mod m)
}
