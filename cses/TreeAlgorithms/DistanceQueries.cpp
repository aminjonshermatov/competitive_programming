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

typedef long long           ll;
typedef long double         ld;
typedef pair<ll, ll>        pll;
typedef pair<int, int>      pii;
typedef pair<ll, int>       pli;
typedef pair<int, ll>       pil;
typedef unsigned long long  ull;

#define fi      first
#define se      second
#define P       pair
#define mp      make_pair
#define pb      push_back
#define eb      emplace_back
#define all(x)  (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x)   (ll)(x.size())

#define rep(i, b)       for (auto i = 0; i < b; ++i)
#define forr(el, cont)  for (auto &el : cont)

template<typename T>             using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename K, typename V> using gp_ht = gp_hash_table<K, V, hash<K>, equal_to<K>, direct_mask_range_hashing<>, linear_probe_fn<>, hash_standard_resize_policy<hash_exponential_size_policy<>, hash_load_check_resize_trigger<>, true>>;

inline constexpr auto  inf = numeric_limits<int>::max();
inline constexpr auto ninf = numeric_limits<int>::min();
inline constexpr int MOD = 1e9 + 7;
inline const ld pi = ::atan2(0, -1);
inline constexpr ld eps = 1e-6;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

template<typename TWeight = int> struct Lca {
    int n, LG;
    vector<vector<pair<int, int>>> g;
    vector<vector<int>> up;
    int timer;
    vector<int> tin, tout;
    bool is_dfs_called;

    explicit Lca(int n_) : n(n_), g(n), up(n), timer(0), tin(n, -1), tout(n, -1), is_dfs_called(false) {
        LG = 31 - __builtin_clz(n);
        for (auto &r : up) r.resize(LG + 1, -1);
    }

    void add_edge(int u, int v, TWeight w = TWeight(0)) {
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    void dfs(int v = 0, int p = 0) {
        is_dfs_called = true;
        up[v][0] = p;
        for (int lg = 1; lg <= LG; ++lg) {
            up[v][lg] = up[up[v][lg - 1]][lg - 1];
        }

        tin[v] = timer++;
        for (auto [u, _] : g[v]) if (u != p) dfs(u, v);
        tout[v] = timer++;
    }

    [[nodiscard]] inline bool is_accessor(int u, int v) const {
        return tin[u] <= tin[v] && tout[v] <= tout[u];
    }

    [[nodiscard]] int operator()(int u, int v) const {
        assert(is_dfs_called);
        if (is_accessor(u, v)) return u;
        if (is_accessor(v, u)) return v;
        for (int lg = LG; ~lg; --lg) {
            if (!is_accessor(up[u][lg], v)) u = up[u][lg];
        }
        return up[u][0];
    }
};

void solve() {
    int n, q; cin >> n >> q;

    Lca lca(n);
    rep(_, n - 1) {
        int u, v; cin >> u >> v, --u, --v;
        if (u == v) continue ;
        lca.add_edge(u, v);
    }
    lca.dfs();

    vector<int> dist(n, inf);
    queue<int> Q;
    Q.emplace(0);
    dist[0] = 0;
    while (!Q.empty()) {
        auto v = Q.front(); Q.pop();
        for (auto [u, _] : lca.g[v]) if (dist[v] + 1 < dist[u]) {
            dist[u] = dist[v] + 1;
            Q.emplace(u);
        }
    }

    rep(_, q) {
        int u, v; cin >> u >> v, --u, --v;
        cout << dist[u] + dist[v] - 2 * dist[lca(u, v)] << '\n';
    }
}

bool is_multi = false;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T = 1;
    if (is_multi) cin >> T;
    for (int tc = 1; tc <= T; ++tc) solve();

    return 0;
}
