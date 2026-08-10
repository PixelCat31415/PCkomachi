// pts: 0-indexed Pt array
void RotSwpLine(int n, PT* pts) {
  using E = pair<PT, pii>;
  vector<E> ev;  // dir, i, j: (i, j)=>(j, i)
  rep(i, n) rep(j, i) {
    PT dir = pts[j] - pts[i];
    halfplane(dir) < 0 ? ev.pb({dir, {i, j}})
      : ev.pb({PT(0, 0) - dir, {j, i}});
  }
  sort(ev.begin(), ev.end(), [&](E e1, E e2) {
    auto pol = (e1.F <=> e2.F);
    return pol < 0 || (pol == 0 &&
        pll(e1.F * pts[e1.S.F], e1.F * pts[e1.S.S])
      < pll(e1.F * pts[e2.S.F], e1.F * pts[e2.S.S]));
  });
  vector<int> ord(n), rk(n);
  iota(ord.begin(), ord.end(), 0);
  sort(ord.begin(), ord.end(), [&](int i, int j) {
    return make_pair(pts[i].y, pts[i].x)
      < make_pair(pts[j].y, pts[j].x);
  });
  rep(i, n) rk[ord[i]] = i;
  init_order(ord);  // ord[*]: point indices
  int ne = (int)ev.size();
  rep(ie, ne) {
    int i, j; tie(i, j) = ev[ie].S;
    update_swap(i, j);  // i, j: point indices
    rk[i]++; rk[j]--;   // rk[point idx]: rank in ord
    tie(ord[rk[i]], ord[rk[i] - 1]) = tie(i, j);
    if(ie == ne - 1 || (ev[ie + 1].F <=> ev[ie].F) != 0) update_ans();
  }
}