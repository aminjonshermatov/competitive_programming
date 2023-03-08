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

void solve() {
    int n, q; cin >> n >> q;
    vector<vector<int>> g(n);

    rep(_, n - 1) {
        int u, v; cin >> u >> v, --u, --v;
        if (u == v) continue ;
        g[u].eb(v);
        g[v].eb(u);
    }

    const int L = 31 - __builtin_clz(n);
    vector<vector<int>> up(n, vector<int>(L + 1, -1));
    vector<int> tin(n), tout(n), dist(n, 0);
    int timer = 0;
    auto dfs = [&](auto f, int v, int p, int d) -> void {
        up[v][0] = p;
        for (int l = 1; l <= L && up[v][l - 1] != -1; ++l) {
            up[v][l] = up[up[v][l - 1]][l - 1];
        }

        dist[v] = d;
        tin[v] = ++timer;
        for (auto u : g[v]) if (u != p) f(f, u, v, d + 1);
        tout[v] = ++timer;
    };
    dfs(dfs, 0, 0, 0);

    auto is_accessor = [&](int u, int v) -> bool {
        return tin[u] <= tin[v] && tout[v] <= tout[u];
    };

    auto lca = [&](int u, int v) -> int {
        if (is_accessor(u, v)) return u;
        if (is_accessor(v, u)) return v;
        for (int l = L; l >= 0; --l) {
            assert(up[u][l] != -1);
            if (!is_accessor(up[u][l], v)) u = up[u][l];
        }
        return up[u][0];
    };

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
