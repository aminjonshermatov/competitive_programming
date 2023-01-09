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
#define sz(x)   (ll)((x).size())

#define rep(i, b)       for (auto i = 0; (i) < (b); ++(i))
#define forr(el, cont)  for (auto &(el) : (cont))

template<typename T>             using ordered_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename K, typename V> using gp_ht = gp_hash_table<K, V, hash<K>, equal_to<K>, direct_mask_range_hashing<>, linear_probe_fn<>, hash_standard_resize_policy<hash_exponential_size_policy<>, hash_load_check_resize_trigger<>, true>>;

const ll inf = 1e9;
const ll MOD = 1e9 + 7;
const ld pi = atan2(0, -1);
const ld eps = 1e-6;

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n, vector<int>(n, 0));
    vector<vector<int>> g(n);
    rep(_, m) {
        int a, b; cin >> a >> b;
        --a, --b;
        adj[a][b] = adj[b][a] = 1;
        g[a].eb(b);
        g[b].eb(a);
    }
    const int st = 0, sk = n-1;

    vector<int> dist(n), pred(n);
    auto bfs = [&]() -> bool {
        fill(all(dist), -1);
        dist[st] = 0;
        queue<int> q;
        q.emplace(st);
        while (!q.empty()) {
            auto v = q.front(); q.pop();
            forr(u, g[v]) if (dist[u] == -1 && adj[v][u] > 0) {
                pred[u] = v;
                dist[u] = dist[v] + 1;
                q.emplace(u);
            }
        }

        return dist[sk] != -1;
    };

    int mx_flow = 0;
    while (bfs()) {
        int cur_f = inf;
        for (auto v = sk; v != st; v = pred[v]) {
            auto u = pred[v]; // u->v
            cur_f = min(cur_f, adj[u][v]);
        }

        mx_flow += cur_f;
        for (auto v = sk; v != st; v = pred[v]) {
            auto u = pred[v]; // u->v
            adj[u][v] -= cur_f;
            adj[v][u] += cur_f;
        }
    }

    //cout << mx_flow << '\n';
    bfs();
    vector<pii> edges;
    rep(v, n) forr(u, g[v]) if (v != u && adj[v][u] == 0 && dist[v] != -1 && dist[u] == -1) edges.eb(v, u);

    cout << sz(edges) << '\n';
    for (auto [v, u] : edges) cout << v + 1 << ' ' << u + 1 << '\n';
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
