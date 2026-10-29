ll findDet(vector<vector<int>> a) {
  int n = a.size();
  assert(n == a[0].size());
  ll det = 1;
  for (int i = 0; i < n; i++) {
    if (!a[i][i]) {
      det = mod - det;
      bool is = false;
      for (int j = i + 1; j < n; j++) if (a[j][i]) {
        swap(a[j], a[i]);
        is = true;
        break;
      }
      if (!is) return 0;
    }
	det = mul(det, a[i][i]);
	int mz = inv(a[i][i]);
    for (int j = 0; j < n; j++)
		a[i][j] = mul(a[i][j], mz);
    for (int j = 0; j < n; j++) if (i ^ j) {
      int mw = a[j][i];
      for (int k = 0; k < n; k++) {
		  add(a[j][k], -mul(a[i][k], mw));
      }
    }
  }
  return det;
}

