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

void solve() {
    int n, q; cin >> n >> q;
    vector<int> A(n);
    for (auto &a : A) cin >> a;

    vector<vector<int>> g(n);
    rep(_, n - 1) {
        int u, v; cin >> u >> v, --u, --v;
        g[u].eb(v);
        g[v].eb(u);
    }

    const int LG = 31 - __builtin_clz(n);
    vector<vector<int>> up(n, vector<int>(LG + 1, -1));
    vector<int> tin(n), tout(n);
    int timer = 0;
    auto dfs = [&](auto f, int v, int p) -> void {
        up[v][0] = p;
        for (int l = 1; l <= LG; ++l) {
            up[v][l] = up[up[v][l - 1]][l - 1];
        }
        tin[v] = timer++;
        forr(u, g[v]) if (p != u) f(f, u, v);
        tout[v] = timer++;
    };

    dfs(dfs, 0, 0);
    FenwickTreePointUpdateRangeQuery<ll> ft(2 * n);
    rep(v, n) ft.modify(tin[v], A[v]);

    rep(_, q) {
        char cmd; cin >> cmd;
        if (cmd == '1') {
            int s, x; cin >> s >> x, --s;
            ft.modify(tin[s], x - A[s]);
            A[s] = x;
        } else if (cmd == '2') {
            int s; cin >> s, --s;
            cout << ft.query(tin[s], tout[s] + 1) << '\n';
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
    cerr << endl << "Time: " << elapsed_ms.count() << " ms\n";
#endif
    return 0;
}
