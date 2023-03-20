// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;
typedef pair<int, ll> pil;
typedef unsigned long long ull;

#define fi first
#define se second
#define P pair
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (ll)(x.size())

#define rep(i, b) for (auto i = 0; i < b; ++i)
#define forr(el, cont) for (auto &el: cont)

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename K, typename V>
using gp_ht = gp_hash_table<K, V, hash<K>, equal_to<K>, direct_mask_range_hashing<>, linear_probe_fn<>, hash_standard_resize_policy<hash_exponential_size_policy<>, hash_load_check_resize_trigger<>, true>>;

inline constexpr auto inf = numeric_limits<int>::max();
inline constexpr auto ninf = numeric_limits<int>::min();
inline constexpr int MOD = 1e9 + 7;
inline const ld pi = ::atan2(0, -1);
inline constexpr ld eps = 1e-6;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

template <typename T = int> struct FenwickTreePointUpdateRangeQuery {
  int n;
  vector<T> bit;

  FenwickTreePointUpdateRangeQuery() = default;
  explicit FenwickTreePointUpdateRangeQuery(int n_) : n(n_), bit(n_, T(0))  { }
  template<typename U = T> explicit FenwickTreePointUpdateRangeQuery(const vector<U> &A) : n(A.size()), bit(A.size(), T(0)) {
    for (auto idx = 0u; idx < n; ++idx) modify(idx, A[idx]);
  }

  void init(int n_) {
    n = n_;
    bit.assign(n, T(0));
  }

  auto modify(int idx, T val) -> void {
    for (; idx < n; idx = idx | (idx + 1)) bit[idx] += val;
  }

  [[nodiscard]] auto query(int idx) const -> T {
    T ret = T(0);
    for (; idx >= 0; idx = (idx & (idx + 1)) - 1) ret += bit[idx];
    return ret;
  }

  [[nodiscard]] auto query(int l, int r) const -> T { // [l, r)
    return query(r - 1) - query(l - 1);
  }

};

const int LG = 20;

struct Edge {
  int from, to;
  ll weight;
};

void solve() {
  int n; cin >> n;
  vector<Edge> edges(n - 1);
  vector<vector<pair<int, int>>> g(n);
  for (int i = 0; i < n - 1; ++i) {
    auto &[u, v, w] = edges[i];
    cin >> u >> v >> w;
    --u, --v;
    g[u].eb(v, i);
    g[v].eb(u, i);
  }

  vector<int> tin_lca(n), tout_lca(n), tin_euler(n), tout_euler(n);
  vector<vector<int>> up(n, vector<int>(LG + 1));
  int timer_lca = 0, timer_euler = 0;
  vector<int> e2v(n - 1, -1);
  auto dfs = [&](auto f, int v, int p) -> void {
    tin_lca[v] = timer_lca++;
    tin_euler[v] = timer_euler++;
    up[v][0] = p;
    for (int l = 1; l <= LG && ~up[v][l - 1]; ++l) {
      up[v][l] = up[up[v][l - 1]][l - 1];
    }
    for (auto [u, idx] : g[v]) if (u != p) f(f, u, v), e2v[idx] = u;
    tout_lca[v] = timer_lca++;
    tout_euler[v] = timer_euler;
  };
  dfs(dfs, 0, 0);

  auto is_accessor = [&](int u, int v) { return tin_lca[u] <= tin_lca[v] && tout_lca[v] <= tout_lca[u]; };
  auto lca = [&](int u, int v) -> int {
    if (is_accessor(u, v)) return u;
    if (is_accessor(v, u)) return v;
    for (int i = LG; ~i; --i) {
      if (!is_accessor(up[u][i], v)) u = up[u][i];
    }
    return up[u][0];
  };

  FenwickTreePointUpdateRangeQuery<ll> ft(2 * n);
  for (int i = 0; i < n - 1; ++i) {
    ft.modify(tin_euler[e2v[i]], edges[i].weight);
    ft.modify(tout_euler[e2v[i]], -edges[i].weight);
  }

  int q; cin >> q;
  rep(_, q) {
    char cmd; cin >> cmd;
    if (cmd == '1') {
      int i;
      ll w;
      cin >> i >> w;
      --i;
      ft.modify(tin_euler[e2v[i]], w - edges[i].weight);
      ft.modify(tout_euler[e2v[i]], edges[i].weight - w);
      edges[i].weight = w;
    } else if (cmd == '2') {
      int u, v; cin >> u >> v;
      --u, --v;
      auto lca_ = lca(u, v);
      cout << ft.query(tin_euler[u]) + ft.query(tin_euler[v]) - 2ll * ft.query(tin_euler[lca_]) << '\n';
    }
  }
}

//#define MEASURE_TIME
bool is_multi = false;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
#ifdef MEASURE_TIME
  auto start = chrono::steady_clock::now();
#endif
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
#ifdef MEASURE_TIME
  auto finish = chrono::steady_clock::now();
  auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(finish - start);
  cerr << endl
       << "Time: " << elapsed_ms.count() << " ms\n";
#endif
  return 0;
}
