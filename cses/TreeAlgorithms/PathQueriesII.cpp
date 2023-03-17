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

template<typename T = ::int32_t> struct SegmentTree {

    static inline constexpr T DEFAULT_VALUE = T(0);
    static inline constexpr T DEFAULT_LAZY = T(0);

    template<typename U> struct Node {
        U val;
        U lazy;
        int right;
        bool has_lazy;

        void apply([[maybe_unused]] int l, [[maybe_unused]] int r, U v) {
            val = v;
            lazy = v;
            has_lazy = false;
        }

        template<typename V> static Node unite(const Node<V> &a, const Node<V> &b) {
            return Node{
                    max(a.val, b.val),
                    DEFAULT_LAZY,
                    b.right,
                    false
            };
        }
    };

    static inline constexpr Node<T> NEUTRAL_ELEMENT = {DEFAULT_VALUE, DEFAULT_LAZY, -1, false};

    int size;
    vector<Node<T>> tree;

    SegmentTree() = default;
    explicit SegmentTree(int n) {
        size = 1;
        while (size < n) size <<= 1;
        tree.assign(2 * size - 1, NEUTRAL_ELEMENT);
        build(0, 0, size);
    }
    template<typename U = T> explicit SegmentTree(vector<U> &A) : SegmentTree(A.size()) {
        size = 1;
        while (size < A.size()) size <<= 1;
        tree.assign(2 * size - 1, NEUTRAL_ELEMENT);
        build(A, 0, 0, size);
    }

    void init(int n) {
        size = 1;
        while (size < n) size <<= 1;
        tree.resize(2 * size - 1);
        build(0, 0, size);
    }

    inline void push(int x, int lx, int rx) {
        if (rx - lx == 1 || !tree[x].has_lazy) return;

        auto mid = lx + (rx - lx) / 2;
        tree[2 * x + 1].apply(lx, mid, tree[x].lazy);
        tree[2 * x + 2].apply(mid, rx, tree[x].lazy);
        tree[x].lazy = DEFAULT_LAZY;
        tree[x].has_lazy = false;
    }

    inline void pull(int x) {
        tree[x] = Node<T>::unite(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void build(int x, int lx, int rx) {
        if (rx - lx == 1) {
            tree[x] = {DEFAULT_VALUE, DEFAULT_LAZY, lx, false};
            return;
        }

        auto mid = lx + (rx - lx) / 2;
        build(2 * x + 1, lx, mid);
        build(2 * x + 2, mid, rx);
        pull(x);
    }

    template<typename U = T>
    void build(vector<U> &A, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < A.size()) tree[x] = {A[lx], DEFAULT_LAZY, lx, false};
            return;
        }

        auto mid = lx + (rx - lx) / 2;
        build(A, 2 * x + 1, lx, mid);
        build(A, 2 * x + 2, mid, rx);
        pull(x);
    }

    void modify(int l, int r, T v, int x, int lx, int rx) {
        push(x, lx, rx);
        if (l >= rx || r <= lx) return;
        if (l <= lx && rx <= r) {
            tree[x].apply(lx, rx, v);
            return;
        }

        auto mid = lx + (rx - lx) / 2;
        modify(l, r, v, 2 * x + 1, lx, mid);
        modify(l, r, v, 2 * x + 2, mid, rx);
        pull(x);
    }

    void modify(int idx, T v) { modify(idx, idx, v, 0, 0, size); }
    void modify(int l, int r, T v) { modify(l, r, v, 0, 0, size); }

    Node<T> query(int l, int r, int x, int lx, int rx) {
        push(x, lx, rx);
        if (l >= rx || r <= lx) return NEUTRAL_ELEMENT;
        if (l <= lx && rx <= r) return tree[x];

        auto mid = lx + (rx - lx) / 2;
        auto res = Node<T>::unite(query(l, r, 2 * x + 1, lx, mid),
                                  query(l, r, 2 * x + 2, mid, rx));
        pull(x);
        return res;
    }

    T query(int l, int r) { return query(l, r, 0, 0, size).val; }
    T query(int idx) { return query(idx, idx + 1, 0, 0, size).val; }

    template<typename Op> T get_first(T v, int i, int x, int lx, int rx, Op &op) {
        if (!op(tree[x].val, v) || tree[x].right < i) return -1;
        if (rx - lx == 1) return lx;

        auto mid = lx + (rx - lx) / 2;
        auto res = get_first(v, i, 2 * x + 1, lx, mid, op);
        if (res == -1) res = get_first(v, i, 2 * x + 2, mid, rx, op);
        return res;
    }

    template<typename Op> T get_first(T v, int i, Op &op) {
        return get_first(v, i, 0, 0, size, op);
    }

    template<typename U>
    friend ostream& operator<<(ostream &out, const SegmentTree<U> &st) {
        for (auto i = 1u, j = 0u; j < st.tree.size(); i <<= 1) {
            auto c = 0u;
            while (c++ < i) out << st.tree[j].val << ',' << st.tree[j++].lazy << ' ';
            out << '\n';
        }
        return out;
    }
};

template<typename T = ::int32_t> struct Hld {
    vector<int> parent, root, depth, treePos, heavy;
    SegmentTree<T> tree;

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
            if (depth[root[u]] > depth[root[v]]) swap(u, v); // u closer to lca rather than v
            op(treePos[root[v]], treePos[v] + 1);
        }
        if (depth[u] > depth[v]) swap(u, v);
        op(treePos[u], treePos[v] + 1);
    }

    void modify(int v, const T &val) {
        modify(v, v, val);
    }
    void modify(int u, int v, const T &val) { // [u, v]
        processPath(u, v, [this, &val](int l, int r) { // [l, r)
            tree.modify(l, r, val);
        });
    }

    T query(int u, int v) { // [u, v]
        T res(numeric_limits<int>::min());
        processPath(u, v, [this, &res](int l, int r) { // [l, r)
            res = max(res, tree.query(l, r));
        });
        return res;
    }
};

void solve() {
    int n, q; cin >> n >> q;
    vector<int> A(n);
    forr(a, A) cin >> a;

    vector<vector<int>> g(n);
    rep(_, n - 1) {
        int u, v; cin >> u >> v;
        --u, --v;
        g[u].eb(v);
        g[v].eb(u);
    }

    Hld hld(g);
    rep(v, n) hld.modify(v, A[v]);

    rep(_, q) {
        char cmd; cin >> cmd;
        if (cmd == '1') {
            int s, x; cin >> s >> x;
            hld.modify(s - 1, x);
        } else if (cmd == '2') {
            int a, b; cin >> a >> b;
            cout << hld.query(a - 1, b - 1) << ' ';
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
    cerr << endl << "Time: " << elapsed_ms.count() << " ms\n";
#endif
    return 0;
}