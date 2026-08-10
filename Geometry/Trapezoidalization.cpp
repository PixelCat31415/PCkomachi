// (FP) needs segment intersect
// set INF per constraints; segments use lex endpoints
const double INF = 0;
template<class T>
struct SweepLine {
  struct cmp {
    cmp(const SweepLine &_swp): swp(_swp) {}
    bool operator()(int a, int b) const {
      if (abs(swp.get_y(a) - swp.get_y(b)) <= swp.eps)
        return swp.slope_cmp(a, b);
      return swp.get_y(a) + swp.eps < swp.get_y(b);
    }
    const SweepLine &swp;
  } _cmp;
  T curTime, eps, curQ;
  vector<Line> base;
  multiset<int, cmp> sweep;
  multiset<pair<T, int>> event;
  using SI = typename multiset<int, cmp>::iterator;
  using EI = typename multiset<pair<T, int>>::iterator;
  vector<SI> its;
  vector<EI> eits;
  bool slope_cmp(int a, int b) const {
    assert(a != -1);
    if (b == -1) return 0;
    return sign((base[a].b - base[a].a) ^
      (base[b].b - base[b].a)) < 0;
  }
  T get_y(int idx) const {
    if (idx == -1) return curQ;
    Line l = base[idx];
    if (l.a.x == l.b.x) return l.b.y;
    return ((curTime - l.a.x) * l.b.y +
      (l.b.x - curTime) * l.a.y) /
      (l.b.x - l.a.x);
  }
  void insert(int idx) {
    its[idx] = sweep.insert(idx);
    if (its[idx] != sweep.begin())
      update_event(*prev(its[idx]));
    update_event(idx);
    event.emplace(base[idx].b.x, idx + 2 * sz(base));
  }
  void erase(int idx) {
    assert(eits[idx] == event.end());
    auto p = sweep.erase(its[idx]);
    its[idx] = sweep.end();
    if (p != sweep.begin())
      update_event(*prev(p));
  }
  void update_event(int idx) {
    if (eits[idx] != event.end())
      event.erase(eits[idx]);
    eits[idx] = event.end();
    auto nxt = next(its[idx]);
    if (nxt == sweep.end() || !slope_cmp(idx, *nxt))
      return;
    auto t = intersect(base[idx].a, base[idx].b,
      base[*nxt].a, base[*nxt].b).x;
    if (t + eps < curTime ||
        t >= min(base[idx].b.x, base[*nxt].b.x))
      return;
    eits[idx] = event.emplace(t, idx + sz(base));
  }
  void swp(int idx) {
    assert(eits[idx] != event.end());
    eits[idx] = event.end();
    int nxt = *next(its[idx]);
    swap((int&)*its[idx], (int&)*its[nxt]);
    swap(its[idx], its[nxt]);
    if (its[nxt] != sweep.begin())
      update_event(*prev(its[nxt]));
    update_event(idx);
  }
  // only expected to call the functions below
  SweepLine(T t, T e, vector<Line> vec):
    _cmp(*this), curTime(t), eps(e), curQ(),
    base(vec), sweep(_cmp), event(),
    its(sz(vec), sweep.end()),
    eits(sz(vec), event.end()) {
    For(i, 0, sz(base) - 1) {
      auto &[p, q] = base[i];
      if (p > q) swap(p, q);
      if (p.x <= curTime && curTime <= q.x)
        insert(i);
      else if (curTime < p.x)
        event.emplace(p.x, i);
    }
  }
  void setTime(T t, bool ers = false) {
    assert(t >= curTime);
    while (!event.empty() && event.begin()->F <= t) {
      auto [et, idx] = *event.begin();
      int s = idx / sz(base);
      idx %= sz(base);
      if (abs(et - t) <= eps && s == 2 && !ers) break;
      curTime = et;
      event.erase(event.begin());
      if (s == 2) erase(idx);
      else if (s == 1) swp(idx);
      else insert(idx);
    }
    curTime = t;
  }
  T nextEvent() {
    if (event.empty()) return INF;
    return event.begin()->F;
  }
  int lower_bound(T y) {
    curQ = y;
    auto p = sweep.lower_bound(-1);
    if (p == sweep.end()) return -1;
    return *p;
  }
};
