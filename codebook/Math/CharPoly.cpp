#define rep(x, y, z) for (int x=y; x<z; x++)
using VI = vector<int>; using VVI = vector<VI>;
void Hessenberg(VVI &H, int N) {
  for (int i = 0; i < N - 2; ++i) {
    for (int j = i + 1; j < N; ++j) if (H[j][i]) {
      rep(k, i, N) swap(H[i+1][k], H[j][k]);
      rep(k, 0, N) swap(H[k][i+1], H[k][j]);
      break;
    }
    if (!H[i + 1][i]) continue;
    for (int j = i + 2; j < N; ++j) {
      int co = mul(modinv(H[i + 1][i]), H[j][i]);
      rep(k, i, N) subeq(H[j][k], mul(H[i+1][k], co));
      rep(k, 0, N) addeq(H[k][i+1], mul(H[k][j], co));
    }
  }
}
VI CharacteristicPoly(VVI A) {
  int N = (int)A.size(); Hessenberg(A, N);
  VVI P(N + 1, VI(N + 1)); P[0][0] = 1;
  for (int i = 1; i <= N; ++i) {
    rep(j, 0, i+1) P[i][j] = j ? P[i-1][j-1] : 0;
    for (int j = i - 1, val = 1; j >= 0; --j) {
      int co = mul(val, A[j][i - 1]);
      rep(k, 0, j+1) subeq(P[i][k], mul(P[j][k], co));
      if (j) val = mul(val, A[j][j - 1]);
    }
  }
  if (N & 1) for (int &x: P[N]) x = sub(0, x);
  return P[N]; // test: 2021 PTZ Korea K
}
