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

  explicit SegmentTree(int n_) : n(n_), tree(2 * n_, ninf) { }

  void set(int pos, int nval) {
    pos += n;
    tree[pos] = nval;
    while (pos > 1) {
      pos >>= 1;
      tree[pos] = max(tree[pos << 1], tree[pos << 1 | 1]);
    }
  }

  int query(int ql, int qr) {
    ql += n; qr += n;
    auto ans = ninf;
    while (ql < qr) {
      if (ql & 1) ans = max(ans, tree[ql++]);
      if (qr & 1) ans = max(ans, tree[--qr]);
      ql >>= 1;
      qr >>= 1;
    }
    return ans;
  }

};

void solve() {
  int n, q;
  cin >> n >> q;
  vector<int> A(n);
  forr(a, A) cin >> a;

  vector<vector<int>> g(n);
  rep(_, n - 1) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    g[u].eb(v);
    g[v].eb(u);
  }

  vector<int> size(n, 0), parent(n, -1), root(n, -1), heavy(n, -1), treePos(n, -1), depth(n);
  auto dfs_size = [&](auto f, int v) -> void {
    size[v] = 1;
    int heavy_v = -1;
    forr(u, g[v]) {
      if (u == parent[v]) continue;
      depth[u] = depth[v] + 1;
      parent[u] = v;
      f(f, u);
      if (heavy_v == -1 || size[heavy_v] < size[u]) {
        heavy_v = u;
      }
    }
    heavy[v] = heavy_v;
  };
  depth[0] = 0;
  dfs_size(dfs_size, 0);

  int cur_pos = 0;
  auto dfs_pos = [&](auto f, int v, int head) -> void {
    treePos[v] = cur_pos++;
    root[v] = head;
    if (heavy[v] != -1) {
      f(f, heavy[v], head);
    }
    forr(u, g[v]) {
      if (u == parent[v] || u == heavy[v]) continue ;
      f(f, u, u);
    }
  };
  dfs_pos(dfs_pos, 0, 0);

  SegmentTree st(n);
  for (int v = 0; v < n; ++v) st.set(treePos[v], A[v]);

  auto qry = [&](int u, int v) -> int {
    auto ans = ninf;
    for (; root[u] != root[v]; u = parent[root[u]]) {
      if (depth[root[v]] > depth[root[u]]) swap(u, v);
      ans = max(ans, st.query(treePos[root[u]], treePos[u] + 1));
    }
    if (depth[u] > depth[v]) swap(u, v); // u is father to root
    ans = max(ans, st.query(treePos[u], treePos[v] + 1));
    return ans;
  };

  auto upd = [&](int v, int nval) {
    st.set(treePos[v], nval);
  };

  rep(_, q) {
    char cmd;
    cin >> cmd;
    if (cmd == '1') {
      int s, x;
      cin >> s >> x;
      upd(s - 1, x);
    } else if (cmd == '2') {
      int a, b;
      cin >> a >> b;
      cout << qry(a - 1, b - 1) << ' ';
    }
  }
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