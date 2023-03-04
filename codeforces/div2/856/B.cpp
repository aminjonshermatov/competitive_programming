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

void solve(vector<int> &A) {
    const int n(sz(A));

    for (int i = 0; i + 1 < n; ++i) {
        if (A[i] == 1) ++A[i];
        if (i > 0 && A[i] % A[i - 1] == 0) ++A[i];
        if (A[i + 1] % A[i] == 0) {
            if (++A[i + 1] == A[i]) ++A[i + 1];

        }
    }
}

bool check(vector<int> &A) {
    const int n(sz(A));
    for (int i = 0; i + 1 < n; ++i) {
        if (A[i + 1] % A[i] == 0) {
            return false;
        }
    }
    return true;
}

void solve() {
    int n; cin >> n;
    vector<int> A(n);
    forr(a, A) cin >> a;
    /*
    rep(_, 1000) {
        int n;
        n = 1 + rnd() % 50;
        vector<int> A(n);
        rep(i, n) A[i] = 1 + rnd() % 50;

        auto B = A;
        solve(A);
        if (!check(A)) {
            cout << "bad: " << '\n';
            forr(a, B) cout << a << ' ' ;
            cout << '\n';
            forr(a, A) cout << a << ' ' ;
            cout << '\n';
            return;
        }
    }*/

    solve(A);
    forr(a, A) cout << a << ' ' ;
    cout << '\n';
}

bool is_multi = true;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T = 1;
    if (is_multi) cin >> T;
    for (int tc = 1; tc <= T; ++tc) solve();

    return 0;
}