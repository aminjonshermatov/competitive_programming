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

inline constexpr auto  inf = numeric_limits<int>::max();
inline constexpr auto ninf = numeric_limits<int>::min();
inline constexpr int MOD = 1e9 + 7;
inline const ld pi = ::atan2(0, -1);
inline constexpr ld eps = 1e-6;

struct segtree {
    int n;
    vector<int> tree;

    explicit segtree(int n_) {
        n = 1;
        while (n < n_) n <<= 1;
        tree.assign(2 * n - 1, inf);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            tree[x] = v;
            return;
        }

        auto mid = lx + (rx - lx) / 2;
        if (i < mid) set(i, v, 2 * x + 1, lx, mid);
        else set(i, v, 2 * x + 2, mid, rx);
        tree[x] = min(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void set(int i, int v) {
        set(i, v, 0, 0, n);
    }

    int get(int l, int r, int x, int lx, int rx) {
        if (l >= rx || r <= lx) return inf;
        if (l <= lx && rx <= r) return tree[x];

        auto mid = lx + (rx - lx) / 2;
        auto lhs = get(l, r, 2 * x + 1, lx, mid);
        auto rhs = get(l, r, 2 * x + 2, mid, rx);
        return min(lhs, rhs);
    }

    int get(int l, int r) {
        return get(l, r, 0, 0, n);
    }
};

void solve() {
    int n, q; cin >> n >> q;
    vector<int> A(n);
    for (auto &a : A) cin >> a;

    segtree left(n), right(n);
    rep(i, n) {
        left.set(i, A[i] - i - 1);
        right.set(i, A[i] + i + 1);
    }

    rep(_, q) {
        char t; cin >> t;
        if (t == '1') {
            int k, x; cin >> k >> x, --k;
            A[k] = x;
            left.set(k, A[k] - k - 1);
            right.set(k, A[k] + k + 1);
        } else if (t == '2') {
            int k; cin >> k;
            /*
            left  = pi - i + k
            right = pi + i - k
            */
            cout << min(left.get(0, k) + k, right.get(k, n) - k) << '\n';
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
