// out[i] = me[0]*out[i-1] + me[1]*out[i-2]+...
vector<int> BerlekampMassey(const vector<int> &output) { // SCOPE HASH
  vector<int> d(output.size() + 1), me, he;
  for (int f = 0, i = 1; i <= sz(output); ++i) {
    for (int j = 0; j < sz(me); ++j)
      add(d[i], mul(output[i - j - 2], me[j]));
    add(d[i], -output[i-1]);
    if (d[i] == 0) continue;
    if (me.empty()) {
      me.resize(f = i);
      continue;
    }
    vector<int> o(i - f - 1);
    int k = mul(d[i], -inv(d[f]));
    o.push_back(-k);
    for (auto x : he) o.push_back(mul(x, k));
    if (o.size() < me.size()) o.resize(me.size());
    for (size_t j = 0; j < me.size(); ++j) add(o[j], me[j]);
    if (i-f+he.size() >= me.size()) he = me, f = i;
    me = o;
  }
  for(auto &h: me) add(h, mod);
  return me;
}

// Finds the k-th coefficient of P / Q in O(d log d log k)
// size of NTT has to > 2 * d
NTT<1<<19, 3> ntt;
int BostanMori(vector<int> P, vector<int> Q, long long k) { // SCOPE HASH
  int d = max((int)P.size(), (int)Q.size() - 1);
  vector M = {P, Q};
  M[0].resize(d, 0);
  M[1].resize(d + 1, 0);
  int sz = (2 * d + 1 == 1 ? 2 : (1 << (__lg(2 * d) + 1)));
  vector<int> Qn(sz);
  vector N(2, vector<int>(sz));
  while(k) {
    fill(iter(Qn), 0);
    for(int i = 0; i < d + 1; i++){
      Qn[i] = M[1][i] * ((i & 1) ? -1 : 1);
      add(Qn[i], mod);
    }
    ntt(Qn, sz, false);
    int t[2] = {(int)k & 1, 0};
    for(int i = 0; i < 2; i++){
      fill(iter(N[i]), 0);
      copy(iter(M[i]), N[i].begin());
      ntt(N[i], sz, false);
      for(int j = 0; j < sz; j++) N[i][j] = mul(N[i][j], Qn[j]);
      ntt(N[i], sz, true);
      for(int j = t[i]; j < 2 * sz(M[i]); j += 2){
        M[i][j >> 1] = N[i][j];
      }
    }
    k >>= 1;
  }
  return mul(M[0][0], inv(M[1][0]));
}
// a_n = \sum_{j=1}^{d} c_j a_(n-j), c_0 = 0 
int LinearRecursion(vector<int> a, vector<int> c, ll k) { // SCOPE HASH
  int d = sz(a), sz = 1; // 1e5, 5s
  while(sz <= 2*d) sz <<= 1;
  c[0] = mod - 1;
  for(auto &i : c) i = i ? mod - i : 0;
  auto A = a; A.resize(sz);
  auto C = c; C.resize(sz);
  ntt(A, sz, false), ntt(C, sz, false);
  for(int i = 0; i < sz; i++) A[i] = mul(A[i], C[i]);
  ntt(A, sz, true);
  A.resize(d);
  return BostanMori(A, c, k);
}
