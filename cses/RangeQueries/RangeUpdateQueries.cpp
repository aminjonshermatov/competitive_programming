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

const ll inf = 1e15;
const ll MOD = 1e9 + 7;
const ld pi = atan2(0, -1);
const ld eps = 1e-6;

template <typename T = int> struct fenwick_tree_range_update_point_query {
    int n;
    vector<T> bit;

    explicit fenwick_tree_range_update_point_query(int n_) : n(n_), bit(n_, T(0))  { }

    template<typename U = T> explicit fenwick_tree_range_update_point_query(const vector<U> &A) : n(A.size()) , bit(A.size(), T(0)) {
        for (auto idx = 0u; idx < n; ++idx) modify(idx, idx + 1, A[idx]);
    }

    auto add(int idx, T val) -> void {
        for (; idx < n; idx = idx | (idx + 1)) bit[idx] += val;
    }

    auto modify(int l, int r, T val) -> void { // [, r)
        add(l, val);
        add(r, -val);
    }

    [[nodiscard]] auto get(int idx) const -> T {
        T ret = T(0);
        for (; idx >= 0; idx = (idx & (idx + 1)) - 1) ret += bit[idx];
        return ret;
    }

};

void solve() {
    int n, q; cin >> n >> q;
    vector<int> A(n);
    forr(_xxx_, A) cin >> _xxx_;

    fenwick_tree_range_update_point_query<ll> ft(A);

    rep(_, q) {
        char t; cin >> t;
        if (t == '1') {
            int a, b, u; cin >> a >> b >> u;
            ft.modify(--a, b, u);
        } else {
            int k; cin >> k; --k;
            cout << ft.get(k) << '\n';
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
