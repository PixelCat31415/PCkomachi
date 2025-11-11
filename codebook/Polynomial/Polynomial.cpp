NTT<131072 * 2, 998244353, 3> ntt;
#define fi(s, n) for (int i = (int)(s); i < (int)(n); ++i)
template<int MAXN, ll P, ll RT> // MAXN = 2^k
struct Poly : vector<ll> { // coefficients in [0, P)
  using vector<ll>::vector;
  int n() const { return (int)size(); } // n() >= 1
  Poly(const Poly &p, int m) : vector<ll>(m) {
    copy_n(p.data(), min(p.n(), m), data());
  }
  Poly& irev() { return reverse(data(), data() + n()), *this; }
  Poly& isz(int m) { return resize(m), *this; }
  Poly& iadd(const Poly &rhs) { // n() == rhs.n()
    fi(0, n()) if (((*this)[i] += rhs[i]) >= P) (*this)[i] -= P;
    return *this;
  }
  Poly& imul(ll k) {
    fi(0, n()) (*this)[i] = (*this)[i] * k % P;
    return *this;
  }
  Poly Mul(const Poly &rhs) const {
    int m = 1;
    while (m < n() + rhs.n() - 1) m <<= 1;
    Poly X(*this, m), Y(rhs, m);
    ntt(X.data(), m), ntt(Y.data(), m);
    fi(0, m) X[i] = X[i] * Y[i] % P;
    ntt(X.data(), m, true);
    return X.isz(n() + rhs.n() - 1);
  }
  Poly Inv() const { // (*this)[0] != 0, 1e5/95ms
    if (n() == 1) return {ntt.minv((*this)[0])};
    int m = 1;
    while (m < n() * 2) m <<= 1;
    Poly Xi = Poly(*this, (n() + 1) / 2).Inv().isz(m);
    Poly Y(*this, m);
    ntt(Xi.data(), m), ntt(Y.data(), m);
    fi(0, m) {
      Xi[i] *= (2 - Xi[i] * Y[i]) % P;
      if ((Xi[i] %= P) < 0) Xi[i] += P;
    }
    ntt(Xi.data(), m, true);
    return Xi.isz(n());
  }
  Poly Sqrt() const { // Jacobi((*this)[0], P) = 1, 1e5/235ms
    if (n() == 1) return {QuadraticResidue((*this)[0], P)};
    Poly X = Poly(*this, (n() + 1) / 2).Sqrt().isz(n());
    return X.iadd(Mul(X.Inv()).isz(n())).imul(P / 2 + 1);
  }
  pair<Poly, Poly> DivMod(const Poly &rhs) const { // (rhs.)back() != 0
    if (n() < rhs.n()) return {{0}, *this};
    const int m = n() - rhs.n() + 1;
    Poly X(rhs); X.irev().isz(m);
    Poly Y(*this); Y.irev().isz(m);
    Poly Q = Y.Mul(X.Inv()).isz(m).irev();
    X = rhs.Mul(Q), Y = *this;
    fi(0, n()) if ((Y[i] -= X[i]) < 0) Y[i] += P;
    return {Q, Y.isz(max(1, rhs.n() - 1))};
  }
  Poly Dx() const {
    Poly ret(n() - 1);
    fi(0, ret.n()) ret[i] = (i + 1) * (*this)[i + 1] % P;
    return ret.isz(max(1, ret.n()));
  }
  Poly Sx() const {
    Poly ret(n() + 1);
    fi(0, n()) ret[i + 1] = ntt.minv(i + 1) * (*this)[i] % P;
    return ret;
  }
  Poly _tmul(int nn, const Poly &rhs) const {
    Poly Y = Mul(rhs).isz(n() + nn - 1);
    return Poly(Y.data() + n() - 1, Y.data() + Y.n());
  }
  vector<ll> _eval(const vector<ll> &x, const vector<Poly> &up) const {
    const int m = (int)x.size();
    if (!m) return {};
    vector<Poly> down(m * 2);
    // down[1] = DivMod(up[1]).second;
    // fi(2, m * 2) down[i] = down[i / 2].DivMod(up[i]).second;
    down[1] = Poly(up[1]).irev().isz(n()).Inv().irev()._tmul(m, *this);
    fi(2, m * 2) down[i] = up[i ^ 1]._tmul(up[i].n() - 1, down[i / 2]);
    vector<ll> y(m);
    fi(0, m) y[i] = down[m + i][0];
    return y;
  }
  static vector<Poly> _tree1(const vector<ll> &x) {
    const int m = (int)x.size();
    vector<Poly> up(m * 2);
    fi(0, m) up[m + i] = {(x[i] ? P - x[i] : 0), 1};
    for (int i = m - 1; i > 0; --i) up[i] = up[i * 2].Mul(up[i * 2 + 1]);
    return up;
  }
  vector<ll> Eval(const vector<ll> &x) const { // 1e5, 1s
    auto up = _tree1(x); return _eval(x, up);
  }
  static Poly Interpolate(const vector<ll> &x, const vector<ll> &y) { // 1e5, 1.4s
    const int m = (int)x.size();
    vector<Poly> up = _tree1(x), down(m * 2);
    vector<ll> z = up[1].Dx()._eval(x, up);
    fi(0, m) z[i] = y[i] * ntt.minv(z[i]) % P;
    fi(0, m) down[m + i] = {z[i]};
    for (int i = m - 1; i > 0; --i) down[i] = down[i * 2].Mul(up[i * 2 + 1]).iadd(down[i * 2 + 1].Mul(up[i * 2]));
    return down[1];
  }
  Poly Ln() const { // (*this)[0] == 1, 1e5/170ms
    return Dx().Mul(Inv()).Sx().isz(n());
  }
  Poly Exp() const { // (*this)[0] == 0, 1e5/360ms
    if (n() == 1) return {1};
    Poly X = Poly(*this, (n() + 1) / 2).Exp().isz(n());
    Poly Y = X.Ln(); Y[0] = P - 1;
    fi(0, n()) if ((Y[i] = (*this)[i] - Y[i]) < 0) Y[i] += P;
    return X.Mul(Y).isz(n());
  }
  // M := P(P - 1). If k >= M, k := k % M + M.
  Poly Pow(ll k) const {
    int nz = 0;
    while (nz < n() && !(*this)[nz]) ++nz;
    if (nz * min(k, (ll)n()) >= n()) return Poly(n());
    if (!k) return Poly(Poly {1}, n());
    Poly X(data() + nz, data() + nz + n() - nz * k);
    const ll c = ntt.mpow(X[0], k % (P - 1));
    return X.Ln().imul(k % P).Exp().imul(c).irev().isz(n()).irev();
  }
  static ll LinearRecursion(const vector<ll> &a, const vector<ll> &coef, ll n) { // a_n = \sum c_j a_(n-j)
    const int k = (int)a.size();
    assert((int)coef.size() == k + 1);
    Poly C(k + 1), W(Poly {1}, k), M = {0, 1};
    fi(1, k + 1) C[k - i] = coef[i] ? P - coef[i] : 0;
    C[k] = 1;
    while (n) {
      if (n % 2) W = W.Mul(M).DivMod(C).second;
      n /= 2, M = M.Mul(M).DivMod(C).second;
    }
    ll ret = 0;
    fi(0, k) ret = (ret + W[i] * a[i]) % P;
    return ret;
  }
  vector<ll> chirp_z(ll c,int m){ // P(c^i) for i=0..m-1
    Poly B=(*this);
    int sz=max(n(),m);
    vector<ll> res(m);
    Poly C(sz * 2), iC(sz);
    ll ic = ntt.minv(c);
    fi(0, sz * 2) C[i] = ntt.mpow(c, 1LL * i * (i - 1) / 2 % (P - 1));
    fi(0, sz) iC[i] = ntt.mpow(ic, 1LL * i * (i - 1) / 2 % (P - 1));
    fi(0, n()) B[i] = B[i] * iC[i] % P;
    B=B.irev().Mul(C);
    fi(0, m) res[i] = B[n()-1+i] * iC[i] % P;
    return res;
  }
  Poly shift_c(ll c) { // P(x+c)
    ll tmp = 1;
    Poly A(n()), B(n() + 1);
    fi(0, n()) {
      A[i] = (*this)[i] * fac[i] % P; // fac[i]=i!
      B[i] = tmp * in[i] % P; // in[i]=inv(i!)
      tmp = tmp * c % P;
    }
    B.irev();
    Poly C = A.Mul(B);
    A.isz(n());
    fi(0, n()) A[i] = C[n() + i] * in[i] % P;
    return A;
  }
  // sum_j w_j[x^j]f^i for i=0,1,...,m
  vector<ll> power_proj(Poly wt, int m) { // 1e5 2s, MAXN >= 4 * n()
    // wt.size() = n(), (*this[0]) == 0
    int sz = 1;
    while (sz < n()) sz <<= 1;
    Poly f(*this, sz);
    wt.isz(sz).irev();
    int k = 1, ksz2 = 2 * sz * k, ksz4 = 4 * sz * k;
    Poly _P(2 * sz, 0), _Q(2 * sz, 0);
    rep(i, sz) _P[i] = wt[i], _Q[i] = (P - f[i]) % P;
    while (sz > 1) {
      Poly R(ksz2);
      rep(i, ksz2) R[i] = (i % 2 == 0 ? _Q[i] : (P - _Q[i]) % P);
      Poly PQ = _P.Mul(R), QQ = _Q.Mul(R);
      PQ.isz(ksz4), QQ.isz(ksz4);
      rep(i, ksz2) {
        if((PQ[ksz2 + i] += _P[i]) >= P) PQ[ksz2 + i] -= P;
        if((QQ[ksz2 + i] += _Q[i] + R[i]) >= P) QQ[ksz2 + i] -= P;
        if(QQ[ksz2 + i] >= P) QQ[ksz2 + i] -= P;
      }
      fill(ALL(_P), 0), fill(ALL(_Q), 0);
      rep(j, 2 * k) rep(i, sz / 2) {
        _P[sz * j + i] = PQ[(2 * sz) * j + (2 * i + 1)];
        _Q[sz * j + i] = QQ[(2 * sz) * j + (2 * i + 0)];
      }
      sz /= 2, k *= 2;
    }
    vector<ll> p(k);
    rep(i, k) p[i] = _P[2 * i];
    reverse(ALL(p));
    p.resize(m + 1);
    return p;
  }
  Poly comp_inv() { // (*this)[0] == 0, (*this)[1] != 0
    Poly X(*this, n()), wt(n(), 0);
    ll ic = ntt.minv((*this)[1]);
    for (auto& x: X) x = x * ic % P;
    wt[n() - 1] = 1;
    vector<ll> A = X.power_proj(wt, n() - 1);
    Poly g(n() - 1);
    rep1(i, n() - 1) g[n() - 1 - i] = (n() - 1) * A[i] % P * ntt.minv(i) % P;
    g = g.Pow(ntt.minv(P - n() + 1));
    g.insert(g.begin(), 0);
    ll p = 1;
    rep(i, g.n()) g[i] = g[i] * p % P, p = p * ic % P;
    return g;
  }
  Poly TMul(const Poly &rhs) const { // this[i] - rhs[j] = k
    return Poly(*this).irev().Mul(rhs).isz(n()).irev();
  }
  Poly composition(Poly g) { // f(g(x)), 1e5 3s, MAXN >= 8n
    auto rec = [&](auto &rec, int n, int k, Poly Q) -> Poly {
      if (n == 1) {
        Poly p(2 * k);
        irev();
        fi(0, k) p[2 * i] = (*this)[i];
        return p;
      }
      Poly R(2 * n * k);
      fi(0, 2 * n * k) R[i] = (i % 2 == 0 ? Q[i] : (P - Q[i]) % P);
      Poly QQ = Q.Mul(R).isz(4 * n * k);
      fi(0, 2 * n * k) {
        QQ[2 * n * k + i] += Q[i] + R[i];
        QQ[2 * n * k + i] %= P;
      }
      Poly nxt_Q(2 * n * k);
      for(int j = 0; j < 2 * k; j++) fi(0, n / 2) {
        nxt_Q[n * j + i] = QQ[(2 * n) * j + (2 * i + 0)];
      }
      Poly nxt_p = rec(rec, n / 2, k * 2, nxt_Q);
      Poly pq(4 * n * k);
      for(int j = 0; j < 2 * k; j++) fi(0, n / 2) {
        pq[(2 * n) * j + (2 * i + 1)] += nxt_p[n * j + i];
        pq[(2 * n) * j + (2 * i + 1)] %= P;
      }
      Poly p(2 * n * k);
      fi(0, 2 * n * k) p[i] = (p[i] + pq[2 * n * k + i]) % P;
      pq.pop_back();
      Poly x = pq.TMul(R);
      fi(0, 2 * n * k) p[i] = (p[i] + x[i]) % P;
      return p;
    };
    int sz = 1;
    while(sz < n() || sz < g.n()) sz <<= 1;
    return isz(sz), rec(rec, sz, 1, g.imul(P-1).isz(2 * sz)).isz(sz).irev();
  }
};
#undef fi
using Poly_t = Poly<131072 * 2, 998244353, 3>;
//template<> decltype(Poly_t::ntt) Poly_t::ntt = {};
