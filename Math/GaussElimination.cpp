using VI = vector<int>; // be careful if A.empty()
using VVI = vector<VI>; // ensure that 0 <= x < mod
pair<VI, VVI> gauss(VVI A, VI b) { // solve Ax=b
  const int N = (int)A.size(), M = (int)A[0].size();
  vector<int> depv, free(M, true); int rk = 0;
  for (int i = 0; i < M; i++) {
    int p = -1;
    for (int j = rk; j < N; j++)
      if (p == -1 || abs(A[j][i]) > abs(A[p][i]))
        p = j;
    if (p == -1 || A[p][i] == 0) continue;
    swap(A[p], A[rk]); swap(b[p], b[rk]);
    const int inv = modinv(A[rk][i]);
    for (int &x : A[rk]) x = mul(x, inv);
    b[rk] = mul(b[rk], inv);
    for (int j = 0; j < N; j++) if (j != rk) {
      int z = A[j][i];
      for (int k = 0; k < M; k++)
        A[j][k] = sub(A[j][k], mul(z, A[rk][k]));
      b[j] = sub(b[j], mul(z, b[rk]));
    }
    depv.push_back(i); free[i] = false; ++rk;
  }
  for (int i = rk; i < N; i++)
    if (b[i] != 0) return {{}, {}}; // not consistent
  VI x(M); VVI h;
  for (int i = 0; i < rk; i++) x[depv[i]] = b[i];
  for (int i = 0; i < M; i++) if (free[i]) {
    h.emplace_back(M); h.back()[i] = 1;
    for (int j = 0; j < rk; j++)
      h.back()[depv[j]] = sub(0, A[j][i]);
  }
  return {x, h}; // solution = x + span(h[i])
}
