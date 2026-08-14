#ifdef zisk
template<class T> void _d(T &&x) {
  if constexpr (ranges::range<T> &&
      !is_convertible_v<T, string_view>) {
    cerr << "{ "; for (auto &&i:x) _d(i); cerr << "} ";
  } else if constexpr (requires { get<0>(x); }) {
    cerr << "( ";
    apply([](auto &&...a){ (_d(a), ...); }, x);
    cerr << ") ";
  } else cerr << x << " ";
}  // ranges::subrange(l, r)
void _db() { cerr << "\e[0m\n"; }
void _db(auto &&...a) {
    cerr << "\e[1;33m"; (_d(a), ...); _db(); }
#define debug(...) _db(#__VA_ARGS__, ":", __VA_ARGS__)
#define safe _db(__PRETTY_FUNCTION__,__LINE__,"safe")
#else
#define safe void()
#define debug(...) void()
#endif
