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

template <typename T, typename Op> struct sparse_table {
    using value_type = T;
    Op op;
    vector<vector<T>> table;

    template<typename U = T> auto build(const vector<U> &A) -> void {
        table.assign(A.size(), {});
        for (auto i = 0u; i < A.size(); ++i) table[i] = {A[i]};
        for (auto l = 1u, j = 0u; 2 * l <= A.size(); ++j, l <<= 1) {
            for (auto i = 0u; i + 2 * l <= A.size(); ++i) {
                table[i].emplace_back(op(table[i][j], table[i + l][j]));
            }
        }
    }

    sparse_table() = default;
    template<typename U = T> explicit sparse_table(const vector<U> &A) { build(A); }
    template<typename U = T> sparse_table(const vector<U> &A, Op &op_) : op(op_) { build(A); }

    [[nodiscard]] auto get(int l, int r) const -> int {
        assert(l < r);
        const auto b = 31 - __builtin_clz(r - l);
        return op(table[l][b], table[r - (1 << b)][b]);
    }
};

void solve() {
    int n, q; cin >> n >> q;
    vector<int> A(n);
    forr(_xxx_, A) cin >> _xxx_;

    auto Min = []<typename T>(const T &lhs, const T &rhs) -> T { return lhs < rhs ? lhs : rhs; };
    sparse_table<int, decltype(Min)> st(A, Min);
    rep(_, q) {
        int a, b; cin >> a >> b;
        cout << st.get(--a, b) << '\n';
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
