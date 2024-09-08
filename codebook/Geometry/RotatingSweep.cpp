// pts: 1-indexed Pt array
int ord[MAXN + 10];
int rk[MAXN + 10];
void rotSwpline(int n, Pt* pts) {
  using E = pair<Pt, pii>;
  vector<E> ev;  // dir, i, j: (i, j)=>(j, i)
  rep1(i, n) rep1(j, i - 1) {
    Pt dir = pts[j] - pts[i];
    upper(dir) ? ev.pb({dir, {i, j}})
               : ev.pb({Pt(0, 0) - dir, {j, i}});
  }
  sort(ev.begin(), ev.end(), [&](E e1, E e2) {
    int pol = polarOri(e1.F, e2.F);
    return pol < 0 || (pol == 0 &&
        pll(e1.F * pts[e1.S.F], e1.F * pts[e1.S.S])
      < pll(e1.F * pts[e2.S.F], e1.F * pts[e2.S.S]));
  });
  iota(ord + 1, ord + n + 1, 1);
  sort(ord + 1, ord + n + 1, [&](int i, int j) {
    return cmpYx(pts[i], pts[j]);
  });
  rep1(i, n) rk[ord[i]] = i;
  // ...init with initial rank...
  int ne = (int)ev.size();
  rep(ie, ne) {
    int i, j; tie(i, j) = ev[ie].S;
    // ...do order update...
    rk[i]++; rk[j]--;
    ord[rk[i]] = i;
    ord[rk[i] - 1] = j;
    if(polarOri(ev[ie + 1].F, ev[ie].F) != 0
      || ie == ne - 1) ; // ...do answer update...
  }
}