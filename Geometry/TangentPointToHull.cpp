// (int) needs cyclic ternary search
// C is nonempty; p is strictly outside C
pii get_tangent(vector<PT> &C, PT p) {
  auto gao = [&](int s) {
    return cyc_tsearch(sz(C), [&](int x, int y)
    { return ori(p, C[x], C[y]) == s; });
  };
  return pii(gao(1), gao(-1));
} // return (a, b), ori(p, C[a], C[b]) >= 0
