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
    int n, m; cin >> n >> m;

    using graph_t = vector<vector<int>>;
    graph_t g(n), gr(n);
    rep(i, n) {
        string s; cin >> s;
        rep(j, m) if (s[j] == '1') g[i].eb(i + j + 1), gr[i + j + 1].eb(i);
    }

    auto bfs = [&](graph_t &G, int s) -> vector<int> {
        vector<int> dist(n, inf);
        dist[s] = 0;

        queue<int> q;
        q.emplace(s);
        dist[s] = 0;
        while (!q.empty()) {
            auto v = q.front(); q.pop();
            forr(u, G[v]) {
                if (dist[v] + 1 < dist[u]) {
                    dist[u] = dist[v] + 1;
                    q.emplace(u);
                }
            }
        }
        return dist;
    };

    auto dist = bfs(g, 0);
    auto distr = bfs(gr, n - 1);

    vector<int> ans(n, inf);
    rep(v, n) if (dist[v] != inf) {
        forr(u, g[v]) if (distr[u] != inf) {
            auto d = dist[v] + distr[u] + 1;
            for (int z = v + 1; z < u; ++z) ans[z] = min(ans[z], d);
        }
    }

    for (int i = 1; i + 1 < n; ++i) cout << (ans[i] == inf ? -1 : ans[i]) << " \n"[i + 1 == n];
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
