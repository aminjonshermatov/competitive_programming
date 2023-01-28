// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

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

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n), gr(n);
    rep(_, m) {
        int u, v; cin >> u >> v;
        --u, --v;
        g[u].eb(v);
        gr[v].eb(u);
    }

    vector<bool> used(n, false);
    vector<int> order;
    order.reserve(n);
    auto top_sort = [&](auto f, int u) -> void {
        used[u] = true;
        forr(v, g[u]) if (!used[v]) f(f, v);
        order.eb(u);
    };

    rep(u, n) if (!used[u]) top_sort(top_sort, u);

    vector<int> comp(n);
    auto dfs_comp = [&](auto f, int u, int c) -> void {
        used[u] = true;
        comp[u] = c;
        forr(v, gr[u]) if (!used[v]) f(f, v, c);
    };

    fill(all(used), false);
    reverse(all(order));
    int c = 0;
    forr(u, order) if (!used[u]) dfs_comp(dfs_comp, u, c++);


    map<int, int> mx;
    rep(u, n) mx[comp[u]] = max(mx[comp[u]], u);

    gr.clear();
    gr.resize(c);
    rep(u, n) forr(v, g[u]) if (comp[u] != comp[v]) gr[comp[u]].eb(comp[v]);

    using ans_t = pair<bool, int>;
    used.resize(c);
    auto dp = [&](auto f, int cu, int cv) -> ans_t {
        cout << cu << ' ' << cv << ' ' << mx[cu] << '\n';
        ans_t ans = pair(cu == cv, mx[cu]);
        forr(v, gr[cu]) if (!used[v]) {
            if (v == cv) return pair(true, mx[v]);
            auto res = f(f, v, cv);
            ans.fi |= res.fi;
            ans.se = max(ans.se, res.se);
        }
        return ans;
    };

    int q; cin >> q;
    rep(_, q) {
        int u, v; cin >> u >> v;
        --u, --v;
        auto res = dp(dp, comp[u], comp[v]);
        cout << (res.fi ? res.se + 1 : -1) << '\n';
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
