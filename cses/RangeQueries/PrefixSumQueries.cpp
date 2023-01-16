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

const ll inf = -1e15;
const ll MOD = 1e9 + 7;
const ld pi = atan2(0, -1);
const ld eps = 1e-6;

struct segtree {
    struct node {
        ll sum, pref;
        node(ll sum, ll pref) : sum(sum), pref(pref) {}
        node(ll x = 0) : sum(x), pref(max(0LL, x)) {}
        friend node operator+(const node& a, const node& b) {
            return {a.sum + b.sum, max(a.pref, a.sum + b.pref)};
        }
    };
    int size;
    vector<node> tree;

    segtree(vector<int> &A) {
        size = 1;
        while (size < sz(A)) size <<= 1;
        tree.assign(2 * size - 1, 0);
        build(A, 0, 0, size);
    }

    auto build(vector<int> &A, int x, int lx, int rx) -> void {
        if (rx - lx == 1) {
            if (lx < sz(A)) tree[x] = node(A[lx]);
            return;
        }

        auto mid = lx + (rx - lx) / 2;
        build(A, 2 * x + 1, lx, mid);
        build(A, 2 * x + 2, mid, rx);
        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }

    auto set(int i, int v, int x, int lx, int rx) -> void {
        if (rx - lx == 1) {
            tree[x] = node(v);
            return;
        }

        auto mid = lx + (rx - lx) / 2;
        if (i < mid) set(i, v, 2 * x + 1, lx, mid);
        else         set(i, v, 2 * x + 2, mid, rx);
        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }

    auto get(int l, int r, int x, int lx, int rx) -> node {
        if (l >= rx || r <= lx) return 0;
        if (l <= lx && rx <= r) return tree[x];

        auto mid = lx + (rx - lx) / 2;
        auto lhs = get(l, r, 2 * x + 1, lx, mid);
        auto rhs = get(l, r, 2 * x + 2, mid, rx);
        return lhs + rhs;
    }

    auto get(int l, int r) -> ll {
        return get(l, r, 0, 0, size).pref;
    }

    auto set(int i, int v) -> void {
        set(i, v, 0, 0, size);
    }
};

void solve() {
    int n, q; cin >> n >> q;
    vector<int> A(n);
    for (auto &a : A) cin >> a;

    segtree st(A);
    rep(_, q) {
        char t; cin >> t;
        if (t == '1') {
            int k, u; cin >> k >> u, --k;
            st.set(k, u);
        } else if (t == '2') {
            int a, b; cin >> a >> b, --a;
            cout << st.get(a, b) << '\n';
        }
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
