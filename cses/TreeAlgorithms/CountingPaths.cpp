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

template <typename T = int> struct fenwick_tree_range_update_range_query {
    int n;
    vector<T> bitA, bitB;

    fenwick_tree_range_update_range_query() = default;
    explicit fenwick_tree_range_update_range_query(int n_) : n(n_), bitA(n_, T(0)), bitB(n_, T(0))  { }

    template<typename U = T> explicit fenwick_tree_range_update_range_query(const vector<U> &A) : n(A.size()) , bitA(A.size(), T(0)), bitB(A.size(), T(0)) {
        for (auto idx = 0u; idx < n; ++idx) modify(idx, idx + 1, A[idx]);
    }

    void init(int n_) {
        n = n_;
        bitA.assign(n, T(0));
        bitB.assign(n, T(0));
    }

    auto add(vector<T> &bit, int idx, T val) -> void {
        for (; idx < n; idx = idx | (idx + 1)) bit[idx] += val;
    }

    auto modify(int l, int r, T val) -> void { // [, r)
        add(bitA, l, val);
        add(bitA, r, -val);
        add(bitB, l, val * (l - 1));
        add(bitB, r, -val * (r - 1));
    }

    [[nodiscard]] auto get(const vector<T> &bit, int idx) const -> T {
        T ret = T(0);
        for (; idx >= 0; idx = (idx & (idx + 1)) - 1) ret += bit[idx];
        return ret;
    }

    [[nodiscard]] auto prefix_sum(int idx) const -> T {
        return get(bitA, idx) * idx - get(bitB, idx);
    }

    [[nodiscard]] auto query(int l, int r) const -> T {
        return prefix_sum(r - 1) - prefix_sum(l - 1);
    }
    [[nodiscard]] auto query(int idx) const -> T {
        return prefix_sum(idx) - prefix_sum(idx - 1);
    }

};

template<typename T = ::int32_t> struct Hld {
    vector<int> parent, root, depth, treePos, heavy;
    fenwick_tree_range_update_range_query<T> tree;

    template<typename G> explicit Hld(const G &g) {
        const int n(g.size());
        parent.assign(n, -1);
        root.assign(n, -1);
        treePos.assign(n, -1);
        heavy.assign(n, -1);
        depth.resize(n);
        depth[0] = 0;
        dfs(g, 0);

        for (int u = 0, currentPos = 0; u < n; ++u) {
            if (parent[u] == -1 || heavy[parent[u]] != u) {
                for (int v = u; ~v; v = heavy[v]) {
                    root[v] = u;
                    treePos[v] = currentPos++;
                }
            }
        }
        tree.init(n);
    }

    template<typename G> int dfs(const G &g, int v) {
        int size = 1, maxSubtree = 0;
        for (auto u : g[v]) if (u != parent[v]) {
            parent[u] = v;
            depth[u] = depth[v] + 1;
            auto subtree = dfs(g, u);
            if (subtree > maxSubtree) {
                heavy[v] = u;
                maxSubtree = subtree;
            }
            size += subtree;
        }
        return size;
    }

    template<typename BinaryOP> void processPath(int u, int v, BinaryOP op) {
        for (; root[u] != root[v]; v = parent[root[v]]) {
            if (depth[root[u]] > depth[root[v]]) swap(u, v); // d[u] < d[v]
            op(treePos[root[v]], treePos[v] + 1);
        }
        if (depth[u] > depth[v]) swap(u, v);
        op(treePos[u], treePos[v] + 1);
    }

    void set(int v, const T &val) {
        tree.modify(treePos[v], treePos[v] + 1, v);
    }
    void modify(int u, int v, const T &val) {
        processPath(u, v, [this, &val](int l, int r) { // [l, r)
            tree.modify(l, r, val);
        });
    }

    T query(int u, int v) {
        T res(0);
        processPath(u, v, [this, &res](int l, int r) { // [l, r)
            res += tree.query(l, r);
        });
        return res;
    }
};

void solve() {
    int n, q; cin >> n >> q;
    vector<vector<int>> g(n);
    rep(_, n - 1) {
        int u, v; cin >> u >> v, --u, --v;
        g[u].eb(v);
        g[v].eb(u);
    }

    Hld hld(g);
    rep(_, q) {
        int u, v; cin >> u >> v, --u, --v;
        hld.modify(u, v, 1);
    }
    vector<int> ans(n);
    rep(v, n) cout << hld.query(v, v) << ' ';
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
    cerr << endl << "Time: " << elapsed_ms.count() << " ms\n";
#endif
    return 0;
}
