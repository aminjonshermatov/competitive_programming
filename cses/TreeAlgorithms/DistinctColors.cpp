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

struct SegmentTree {
  int n;
  vector<int> tree;

  explicit SegmentTree(size_t n_) {
    n = 1;
    while (n < n_) n <<= 1;
    tree.assign(2 * n - 1, 0);
  }

  void set(int pos, int val, int x, int lx, int rx) {
    if (rx - lx == 1) {
      tree[x] = val;
      return ;
    }
    auto mid = lx + (rx - lx) / 2;
    if (pos < mid) set(pos, val, 2 * x + 1, lx, mid);
    else set(pos, val, 2 * x + 2, mid, rx);
    tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
  }

  void set(int pos, int val) {
    set(pos, val, 0, 0, n);
  }

  int sum(int ql, int qr, int x, int lx, int rx) {
    if (ql >= rx || qr <= lx) return 0;
    if (ql <= lx && rx <= qr) return tree[x];
    auto mid = lx + (rx - lx) / 2;
    return sum(ql, qr, 2 * x + 1, lx, mid) + sum(ql, qr, 2 * x + 2, mid, rx);
  }

  int sum(int l, int r) { // [l, r)
    return sum(l, r, 0, 0, n);
  }
};

struct Event {
  int v;
  bool is_open;
  Event(int v_, bool is_open_) : v(v_), is_open(is_open_) { }
};

void solve() {
  int n; cin >> n;
  vector<int> A(n);
  forr(a, A) cin >> a;

  vector<vector<int>> g(n);
  rep(_, n - 1) {
    int u, v; cin >> u >> v;
    --u, --v;
    g[u].eb(v);
    g[v].eb(u);
  }

  vector<Event> evs;
  evs.reserve(2 * n);
  auto dfs = [&](auto f, int v, int p) -> void {
    evs.emplace_back(v, true);
    forr(u, g[v]) if (u != p) f(f, u, v);
    evs.emplace_back(v, false);
  };
  dfs(dfs, 0, 0);
  map<int, int> last;
  SegmentTree st(2 * evs.size());
  vector<int> ans(n), tin(n);
  for (int i = 0; i < evs.size(); ++i) {
    auto [v, is_open] = evs[i];
    if (!is_open) {
      ans[v] = st.sum(tin[v], i);
    } else {
      if (last.count(A[v]) > 0) st.set(last[A[v]], 0);
      last[A[v]] = i;
      tin[v] = i;
      st.set(i, 1);
    }
  }

  forr(a, ans) cout << a << ' ';
  cout << '\n';
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
