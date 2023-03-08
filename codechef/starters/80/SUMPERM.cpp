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

bool ok(vector<int> &p) {
    if (clamp<int>(p[0], 1, p.size()) != p[0]) return false;
    int s = p[0];
    for (int i = 1; i < p.size(); ++i) {
        if (clamp<int>(p[i], 1, p.size()) != p[i]) return false;
        if ((s += p[i]) % (i + 1) == 0) return false;
    }
    return true;
}

pair<bool, vector<int>> solve(int n) {
    vector<int> pp(n);
    pp[0] = 1; pp[1] = 2;
    for (int i = 2, ev = 2, od = 1; i < n; ++i) {
        if (i & 1) pp[i] = od += 2;
        else pp[i] = ev += 2;
    }
    if (ok(pp)) return {true, pp};
    return {false, {}};
}

pair<bool, vector<int>> brut(int n) {
    vector<int> p(n);
    iota(all(p), 1);
    do {
        if (ok(p)) return {true, p};
    } while (next_permutation(all(p)));
    return {false, {}};
}

//#define TEST

void solve() {
    int n;
#ifndef TEST
    cin >> n;
#else
    n = rnd() % 10 + 1;
#endif

    auto [ok1, p1] = solve(n);
#ifndef TEST
    if (!ok1) {
        cout << -1 << '\n';
        return;
    }
    forr(a, p1) cout << a << ' ';
    cout << '\n';
#else
    auto [ok2, p2] = brut(n);
    if (!ok1 && ok2) {
        cout << "bad:\n";
        forr(a, p1) cout << a << ' ';
        cout << '\n';
        forr(a, p2) cout << a << ' ';
        cout << '\n';
    }
#endif
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
