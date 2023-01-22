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

inline constexpr auto  inf = numeric_limits<int>::max();
inline constexpr auto ninf = numeric_limits<int>::min();
inline constexpr int MOD = 1e9 + 7;
inline const ld pi = ::atan2(0, -1);
inline constexpr ld eps = 1e-6;

template <typename T = int> struct fenwick_tree_2d_point_update_range_query {
    int n, m;
    vector<vector<T>> bit;

    explicit fenwick_tree_2d_point_update_range_query(int n_, int m_) : n(n_), m(m_), bit(n_, vector<T>(m_, T(0)))  { }

    template<typename U = T> explicit fenwick_tree_2d_point_update_range_query(const vector<vector<U>> &A) : n(A.size()), m(A[0].size()), bit(A.size(), vector<U>(A[0].size(), T(0))) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                add(i, j, A[i][j]);
            }
        }
    }

    auto add(int y, int x, T val) -> void {
        for (int i = y; i < n; i = i | (i + 1)) {
            for (int j = x; j < m; j = j | (j + 1)) {
                bit[i][j] += val;
            }
        }
    }

    [[nodiscard]] auto get(int y, int x) const -> T {
        T ret = T(0);
        for (int i = y; i >= 0; i = (i & (i + 1)) - 1) {
            for (int j = x; j >= 0; j = (j & (j + 1)) - 1) {
                ret += bit[i][j];
            }
        }
        return ret;
    }

    [[nodiscard]] auto get(int y1, int x1, int y2, int x2) const -> T { // [l, r)
        auto res = get(y2 - 1, x2 - 1);
        if (y1 > 0) res -= get(y1 - 1, x2 - 1);
        if (x1 > 0) res -= get(y2 - 1, x1 - 1);
        if (y1 > 0 && x1 > 0) res += get(y1 - 1, x1 - 1);
        return res;
    }

};

void solve() {
    int n, q; cin >> n >> q;
    vector<vector<int>> g(n, vector<int>(n));
    rep(i, n) rep(j, n) {
        char x; cin >> x;
        g[i][j] = x == '*';
    }

    fenwick_tree_2d_point_update_range_query<> ft(g);

    rep(_, q) {
        char t; cin >> t;
        if (t == '1') {
            int y, x; cin >> y >> x;
            ft.add(y - 1, x - 1, g[y - 1][x - 1] == 1 ? -1 : 1);
            g[y - 1][x - 1] ^= 1;
        } else if (t == '2') {
            int y1, x1, y2, x2; cin >> y1 >> x1 >> y2 >> x2;
            cout << ft.get(y1 - 1, x1 - 1, y2, x2) << '\n';
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
