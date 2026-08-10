// may need fac ivf
// == PART HASH ==
#define fi(s, n) for (int i = (int)(s); i < (int)(n); i++)
#define neg(x) (x ? mod - x : 0)
#define V (*this)
template <int MAXN, int RT>  // MAXN = 2^k
struct Poly : vector<int> { // coefficients in [0, P)
  using vector<int>::vector;
  static inline NTT<MAXN, RT> ntt;
  int n() const { return (int)size(); }  // n() >= 1
  Poly(const Poly &p, int m) : vector<int>(m) { copy_n(p.data(), min(p.n(), m), data()); }
  Poly &irev() { return reverse(data(), data() + n()), V; }
  Poly &isz(int m) { return resize(m), V; }
  // == PART HASH ==
  Poly &iadd(const Poly &rhs) { // SCOPE HASH
    fi(0, n()) add(V[i], rhs[i]);
    return V; // need n() == rhs.n() 
  }
  Poly &imul(int k) { // SCOPE HASH
    fi(0, n()) V[i] = mul(V[i], k);
    return V;
  }
  Poly &mul_xk(int m){ // SCOPE HASH
    if(m<0) erase(begin(), begin()+(-m));
    else if(m>0) insert(begin(), m, 0);
    return V;
  }
  Poly Mul(const Poly &rhs) const { // SCOPE HASH
    int m = 1;
    while (m < n() + rhs.n() - 1) m <<= 1;
    assert(m <= MAXN);
    Poly X(V, m), Y(rhs, m);
    ntt(X, m); ntt(Y, m);
    fi(0, m) X[i] = mul(X[i], Y[i]);
    ntt(X, m, true);
    return X.isz(n() + rhs.n() - 1);
  }
  Poly Inv() const { // SCOPE HASH
    if (n() == 1) return {inv(V[0])};
    int m = 1; // need V[0] != 0, 2*sz<=MAXN
    while (m < n() * 2) m <<= 1;
    assert(m <= MAXN);
    Poly Xi = Poly(V, (n() + 1) / 2).Inv().isz(m);
    Poly Y(V, m);
    ntt(Xi, m); ntt(Y, m);
    fi(0, m) {
      Xi[i] = mul(Xi[i], (2 - mul(Xi[i], Y[i])));
      add(Xi[i], mod);
    }
    ntt(Xi, m, true);
    return Xi.isz(n());
  }
  // == PART HASH ==
  Poly &shift_inplace(const int &c) { // need fac[], ivf[]
    int n = V.n(); // 2 * sz <= MAXN
    for (int i = 0; i < n; i++) V[i] = mul(V[i], fac[i]);
    Poly g(n);
    int cp = 1;
    for (int i = 0; i < n; i++){
      g[i] = mul(cp, ivf[i]); 
      cp = mul(cp, c);
    }	
    V = V.irev().Mul(g).isz(n).irev();
    for (int i = 0; i < n; i++) V[i] = mul(V[i], ivf[i]);
    return V;
  }
  Poly Shift(const int &c) const { return Poly(V).shift_inplace(c); }
  // == PART HASH ==
  Poly Dx() const {
    Poly ret(n() - 1);
    fi(0, ret.n()) ret[i] = mul(i+1, V[i+1]);
    return ret.isz(max(1, ret.n()));
  }
  Poly Sx() const {
    Poly ret(n() + 1);
    fi(0, n()) ret[i + 1] = mul(inv(i+1), V[i]);
    return ret;
  }
  // == PART HASH ==
  Poly Ln() const {  // V[0] == 1, 2*sz<=MAXN
    return Dx().Mul(Inv()).Sx().isz(n());
  }
  Poly Exp() const {	// V[0] == 0,2*sz<=MAXN
    if (n() == 1) return {1};
    Poly X = Poly(V, (n() + 1) / 2).Exp().isz(n());
    Poly Y = X.Ln();
    Y[0] = mod - 1;
    fi(0, n()){	
      Y[i] = V[i] - Y[i];
      add(Y[i], mod);
    }	
    return X.Mul(Y).isz(n());
  }
  // == PART HASH ==
  // M := P(P - 1). If k >= M, k := k % M + M.
  Poly Pow(ll k) const {	// 2*sz<=MAXN
    int nz = 0;
    while (nz < n() && !V[nz]) nz++;
    if (nz * min(k, (ll)n()) >= n()) return Poly(n());
    if (!k) return Poly(Poly{1}, n());
    Poly X(data() + nz, data() + nz + n() - nz * k);
    const int c = po(X[0], k % (mod - 1));
    return X.Ln().imul(k % mod).Exp().imul(c).irev().isz(n()).irev();
  }
  // == PART HASH ==
  Poly _tmul(int nn, const Poly &rhs) const {
    Poly Y = Mul(rhs).isz(n() + nn - 1);
    return Poly(Y.data() + n() - 1, Y.data() + Y.n());
  }
  vector<int> _eval(const vector<int> &x, const vector<Poly> &up) const { // SCOPE HASH
    const int m = (int)x.size();
    if (!m) return {};
    vector<Poly> down(m * 2);
    down[1] = Poly(up[1]).irev().isz(n()).Inv().irev()._tmul(m, V);
    fi(2, m * 2) down[i] = up[i ^ 1]._tmul(up[i].n() - 1, down[i / 2]);
    vector<int> y(m);
    fi(0, m) y[i] = down[m + i][0];
    return y;
  }
  static vector<Poly> _tree1(const vector<int> &x) { // SCOPE HASH
    const int m = (int)x.size();
    vector<Poly> up(m * 2);
    fi(0, m) up[m + i] = {neg(x[i]), 1};
    for (int i = m - 1; i > 0; --i) up[i] = up[i * 2].Mul(up[i * 2 + 1]);
    return up;
  }
  vector<int> Eval(const vector<int> &x) const {  
    auto up = _tree1(x); // 2^17, 1.8s
    return _eval(x, up);
  }
  // == PART HASH ==
  static Poly Interpolate(const vector<int> &x, const vector<int> &y) {	// SCOPE HASH
    const int m = (int)x.size(); // 2^17, 2.3s
    vector<Poly> up = _tree1(x), down(m * 2);
    vector<int> z = up[1].Dx()._eval(x, up);
    fi(0, m) z[i] = mul(y[i], inv(z[i]));
    fi(0, m) down[m + i] = {z[i]};
    for (int i = m - 1; i > 0; --i)
      down[i] = down[i * 2].Mul(up[i * 2 + 1]).iadd(down[i * 2 + 1].Mul(up[i * 2]));
    return down[1];
  }
  pair<Poly, Poly> DivMod(const Poly &rhs) const { // SCOPE HASH
    if (n() < rhs.n()) return {{0}, V}; // 5e5, 0.9s
    const int m = n() - rhs.n() + 1;
    Poly X(rhs); // (rhs.)back() != 0 
    X.irev().isz(m);
    Poly Y(V); Y.irev().isz(m);
    Poly Q = Y.Mul(X.Inv()).isz(m).irev();
    X = rhs.Mul(Q), Y = V;
    fi(0, n()) add(Y[i], -X[i]);
    return {Q, Y.isz(max(1, rhs.n() - 1))};
  }
  // == PART HASH ==
  Poly _Sqrt() const {  // Jacobi(V[0], P) = 1
    if (n() == 1) return {QuadraticResidue(V[0], mod)};
    Poly X = Poly(V, (n() + 1) / 2)._Sqrt().isz(n());
    return X.iadd(Mul(X.Inv()).isz(n())).imul(mod / 2 + 1);
  }
  Poly Sqrt() const {	// SCOPE HASH
    Poly a; // 2 * sz <= MAXN 
    bool has = 0;
    for (int i = 0; i < n(); i++) {
      if (V[i]) has = 1;
      if (has) a.push_back(V[i]);
    }
    if (!has) return V;
    if ((n() + a.n()) % 2 || Jacobi(a[0], mod) != 1) {
      return Poly();
    }
    a = a.isz((n() + a.n()) / 2)._Sqrt();
    int sz = a.n();
    a.isz(n());
    rotate(a.begin(), a.begin() + sz, a.end());
    return a;
  }
  // == PART HASH ==
  Poly Shift_samples(int c, int m){ 
    // V = \sum f(n) x^n, return f(c), ..., f(c+m-1); 2^19, 2s
    Poly A=V;
    Poly Q(n()+1), S(n());
    int nw=1;
    fi(0, n()+1) { Q[i] = mul(1-2*(i&1), nw); nw = mul(nw, n()-i, inv(i+1));}
    nw=1;
    fi(0, n()) { S[i] = mul(1-2*(i&1), nw); nw = mul(nw, c-i, inv(i+1));}
    S=S.Shift(1);
    fi(0,n()) if(i&1) {S[i] = mul(S[i],-1); add(S[i], mod);};
    Poly C=Mul(Q).mul_xk(-n());
    auto tmp=Q.isz(m).Inv();
    C=C.imul(-1).Mul(tmp).isz(m).mul_xk(n());
    A=A.isz(n()+m).iadd(C).irev().isz(n()+m);
    return A.Mul(S).mul_xk(-n()+1).isz(m+1).irev();
  }
  // == PART HASH ==
  Poly power_projection(Poly wt, int m) {	// SCOPE HASH
    assert(n() == wt.n()); // 4*sz <= MAXN
    if (!n()) return Poly(m + 1, 0);
    if (V[0] != 0) {
      int c = V[0];
      V[0] = 0;
      Poly A = V.power_projection(wt, m);
      fi(0, m + 1) A[i] = mul(A[i], fac[i]);
      Poly B(m + 1);
      int pow = 1;
      fi(0, m + 1) {B[i] = mul(pow, ivf[i]); pow = mul(pow, c);}  // inv. of fac
      A = A.Mul(B).isz(m + 1);
      fi(0, m + 1) A[i] = mul(A[i], fac[i]);
      return A;
    }
    int n = 1;
    while (n < V.n()) n *= 2;
    isz(n), wt.isz(n).irev();
    int k = 1;
    Poly p(wt, 2 * n), q(V, 2 * n);
    q.imul(mod - 1);
    while (n > 1) {
      Poly r(2 * n * k);
      fi(0, 2 * n * k) r[i] = (i % 2 == 0 ? q[i] : neg(q[i]));
      Poly pq = p.Mul(r).isz(4 * n * k);
      Poly qq = q.Mul(r).isz(4 * n * k);
      fi(0, 2 * n * k) {
        add(pq[2 * n * k + i], p[i]);
        add(qq[2 * n * k + i], (q[i] + r[i]) % mod);
      }
      fill(p.begin(), p.end(), 0);
      fill(q.begin(), q.end(), 0);
      for(int j = 0; j < 2 * k; j++) fi(0, n / 2) {
        p[n * j + i] = pq[(2 * n) * j + (2 * i + 1)];
        q[n * j + i] = qq[(2 * n) * j + (2 * i + 0)];
      }
      n /= 2; k *= 2;
    }
    Poly ans(k);
    fi(0, k) ans[i] = p[2 * i];
    return ans.irev().isz(m + 1);
  }
  Poly FPSinv() { // SCOPE HASH
    const int n = V.n() - 1; // 2^17, 4s
    if (n == -1) return {};
    assert(V[0] == 0);
    if (n == 0) return V;
    assert(V[1] != 0);
    int c = V[1], ic = inv(c);
    imul(ic);
    Poly wt(n + 1);
    wt[n] = 1;
    Poly A = V.power_projection(wt, n);
    Poly g(n);
    fi(1, n + 1) g[n - i] = mul(n, A[i], inv(i));
    g = g.Pow(neg(inv(n)));
    g.insert(g.begin(), 0);
    int pow = 1;
    fi(0, g.n()) {g[i] = mul(g[i], pow); pow = mul(pow, ic);}
    return g;
  }
  // == PART HASH ==
  Poly TMul(const Poly &rhs) const { // this[i] - rhs[j] = k;
    return Poly(V).irev().Mul(rhs).isz(n()).irev();
  }
  Poly comp_rec(int n, int k, Poly Q){ // SCOPE HASH 
    if (n == 1) {
      Poly p(2 * k);
      irev();
      fi(0, k) p[2 * i] = V[i];
      return p;
    }
    Poly R(2 * n * k);
    fi(0, 2 * n * k) R[i] = (i % 2 == 0 ? Q[i] : neg(Q[i]));
    Poly QQ = Q.Mul(R).isz(4 * n * k);
    fi(0, 2 * n * k)
      add(QQ[2 * n * k + i], (Q[i] + R[i]) % mod);
    Poly nxt_Q(2 * n * k);
    for(int j = 0; j < 2 * k; j++) fi(0, n / 2)
      nxt_Q[n * j + i] = QQ[(2 * n) * j + (2 * i + 0)];
    Poly nxt_p = comp_rec(n / 2, k * 2, nxt_Q);
    Poly pq(4 * n * k);
    for(int j = 0; j < 2 * k; j++) fi(0, n / 2)
      add(pq[(2 * n) * j + (2 * i + 1)], nxt_p[n * j + i]);
    Poly p(2 * n * k);
    fi(0, 2 * n * k) add(p[i], pq[2 * n * k + i]);
    pq.pop_back();
    Poly x = pq.TMul(R);
    fi(0, 2 * n * k) add(p[i], x[i]);
    return p;
  }
  Poly FPScomp(Poly g) { // solves V(g(x))
    int sz = 1; // 2^17, 5s
    while(sz < n() || sz < g.n()) sz <<= 1;
    return isz(sz), comp_rec(sz, 1, g.imul(mod-1).isz(2 * sz)).isz(sz).irev();
  }
  // == PART HASH ==
};
#undef fi
#undef V
#undef neg
using Poly_t = Poly<1 << 21, 3>;
