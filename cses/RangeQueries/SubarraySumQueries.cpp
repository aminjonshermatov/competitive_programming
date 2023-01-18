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

template<typename T>             using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename K, typename V> using gp_ht = gp_hash_table<K, V, hash<K>, equal_to<K>, direct_mask_range_hashing<>, linear_probe_fn<>, hash_standard_resize_policy<hash_exponential_size_policy<>, hash_load_check_resize_trigger<>, true>>;

const ll inf = 1e15;
const ll MOD = 1e9 + 7;
const ld pi = atan2(0, -1);
const ld eps = 1e-6;

struct segtree {
    struct node { ll sum, pf, sf, mx; };

    int n;
    vector<node> tree;

    explicit segtree(vector<int> &A) {
        n = 1;
        while (n < sz(A)) n <<= 1;
        tree.assign(2 * n - 1, make_node(0));
        build(A, 0, 0, n);
    }

    static inline node unite(const node &lhs, const node &rhs) {
        return node{
            lhs.sum + rhs.sum,
            max(lhs.pf, lhs.sum + rhs.pf),
            max(rhs.sf, rhs.sum + lhs.sf),
            max(lhs.sf + rhs.pf, max(lhs.mx, rhs.mx))
        };
    }

    static inline node make_node(ll x) { return node{x, x, x, max<ll>(0, x)}; }

    void build(vector<int> &A, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < sz(A)) tree[x] = make_node(A[lx]);
            return;
        }

        auto mid = lx + (rx - lx) / 2;
        build(A, 2 * x + 1, lx, mid);
        build(A, 2 * x + 2, mid, rx);
        tree[x] = unite(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            tree[x] = make_node(v);
            return;
        }

        auto mid = lx + (rx - lx) / 2;
        if (i < mid) set(i, v, 2 * x + 1, lx, mid);
        else set(i, v, 2 * x + 2, mid, rx);
        tree[x] = unite(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void set(int i, int v) {
        set(i, v, 0, 0, n);
    }

    node get(int l, int r, int x, int lx, int rx) {
        if (l >= rx || r <= lx) return make_node(0);
        if (l <= lx && rx <= r) return tree[x];

        auto mid = lx + (rx - lx) / 2;
        auto lhs = get(l, r, 2 * x + 1, lx, mid);
        auto rhs = get(l, r, 2 * x + 2, mid, rx);
        return unite(lhs, rhs);
    }

    ll get(int l, int r) {
        return get(l, r, 0, 0, n).mx;
    }
};

void solve() {
    int n, m; cin >> n >> m;
    vector<int> A(n);
    for (auto &a : A) cin >> a;

    segtree st(A);

    rep(_, m) {
        int k, x; cin >> k >> x, --k;
        st.set(k, x);
        cout << st.get(0, n) << '\n';
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
