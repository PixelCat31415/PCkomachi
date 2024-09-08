// by LittleCube8152. using N + 2M variables
const int mxM = 25;
const int mxN = 25 + 2 * mxM;
struct simplex {
  const double inf = 1 / .0, eps = 1e-9;
  int n, m, k, var[mxN], inv[mxN], art[mxN];
  double A[mxM][mxN], B[mxM], x[mxN];
  void init(int _n) { n = _n, m = 0; }
  void equation(vector<double> a, double b) {
    for (int i = 0; i < n; i++) A[m][i] = a[i];
    B[m] = b, var[m] = n + m, ++m;
  }
  void pivot(int r, int c, double bx) {
    for (int i = 0; i <= m + 1; i++)
      if (i != r && abs(A[i][c]) > eps) {
        x[var[i]] -= bx * A[i][c] / A[i][var[i]];
        double f = A[i][c] / A[r][c];
        for (int j = 0; j <= n + m + k; j++)
          A[i][j] -= A[r][j] * f;
        B[i] -= B[r] * f;
      }
  }
  double phase(int p) {
    while (true) {
      int in = min_element(
                 A[m + p], A[m + p] + n + m + k + 1) -
        A[m + p];
      if (A[m + p][in] >= -eps) break;
      double bx = inf;
      int piv = -1;
      for (int i = 0; i < m; i++)
        if (A[i][in] > eps && B[i] / A[i][in] <= bx)
          piv = i, bx = B[i] / A[i][in];
      if (piv == -1) return inf;
      int out = var[piv];
      pivot(piv, in, bx);
      x[out] = 0, x[in] = bx, var[piv] = in;
    }
    return x[n + m];
  }
  double solve(vector<double> c) {
    auto invert = [&](int r) {
      for (int j = 0; j <= n + m; j++) A[r][j] *= -1;
      B[r] *= -1;
    };
    k = 1;
    for (int i = 0; i < n; i++) A[m][i] = -c[i];
    fill(A[m + 1], A[m + 1] + mxN, 0.0);
    for (int i = 0; i <= m + 1; i++)
      fill(A[i] + n, A[i] + n + m + 2, 0.0),
        var[i] = n + i, A[i][n + i] = 1;

    for (int i = 0; i < m; i++) {
      if (B[i] < 0) {
        ++k;
        for (int j = 0; j <= n + m; j++)
          A[m + 1][j] += A[i][j];
        invert(i);
        var[i] = n + m + k, A[i][var[i]] = 1,
        art[var[i]] = n + i;
      }
      x[var[i]] = B[i];
    }

    phase(1);
    if (*max_element(
          x + (n + m + 2), x + (n + m + k + 1)) > eps)
      return .0 / .0;
    for (int i = 0; i <= m; i++)
      if (var[i] > n + m)
        var[i] = art[var[i]], invert(i);
    k = 0;
    return phase(0);
  }
} lp;