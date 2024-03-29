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

inline constexpr auto  inf = numeric_limits<ll>::max();
inline constexpr auto ninf = numeric_limits<int>::min();
inline constexpr int MOD = 1e9 + 7;
inline const ld pi = ::atan2(0, -1);
inline constexpr ld eps = 1e-6;

class Dsu {
    int n;
    vector<int> parent, rank;
public:
    explicit Dsu(int n_) : n(n_) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
        rank.assign(n, 1);
    }

    auto find(int v) -> int {
        assert(0 <= v && v < n);
        if (parent[v] != v) parent[v] = find(parent[v]);
        return parent[v];
    }

    auto merge(int v, int u) -> int {
        assert(0 <= v && v < n);
        assert(0 <= u && u < n);
        auto pv = find(v);
        auto pu = find(u);
        if (pv == pu) return pv;

        if (rank[pv] < rank[pu]) swap(pv, pu);
        parent[pu] = pv;
        if (rank[pv] == rank[pu]) ++rank[pv];
        return pv;
    }

    auto is_same(int v, int u) -> bool {
        assert(0 <= v && v < n);
        assert(0 <= u && u < n);
        return find(v) == find(u);
    }
};

void solve() {
    int n, m, Q; cin >> n >> m >> Q;
    vector<vector<pii>> g(n);

    Dsu dsu(n);
    rep(_, m) {
        int a, b, c; cin >> a >> b >> c;
        --a, --b;
        dsu.merge(a, b);
        g[a].eb(b, c);
        g[b].eb(a, -c);
    }

    vector<ll> dist(n, inf);
    vector<bool> is_inf(n, false);
    rep(i, n) if (dsu.find(i) == i) {
        queue<int> q;
        q.emplace(i);
        dist[i] = 0;
        while (!q.empty()) {
            auto u = q.front(); q.pop();
            for (auto [v, c] : g[u]) {
                if (dist[v] == inf) {
                    dist[v] = dist[u] + c;
                    q.emplace(v);
                } else if (dist[v] != dist[u] + c) is_inf[i] = true;
            }
        }
    }

    rep(_, Q) {
        int x, y; cin >> x >> y;
        --x, --y;
        if (dsu.find(x) != dsu.find(y)) cout << "nan";
        else if (is_inf[dsu.find(x)]) cout << "inf";
        else cout << dist[y] - dist[x];
        cout << '\n';
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
