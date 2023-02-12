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

void solve() {
    int sx, sy, tx, ty; cin >> sx >> sy >> tx >> ty;

    auto get_path = [&]() -> pair<string, string> {
        string p1;
        p1.append(ty - sy, 'U');
        p1.append(tx - sx, 'R');
        string p2;
        p2.append(tx - sx, 'R');
        p2.append(ty - sy, 'U');
        return {p1, p2};
    };

    auto rev = [&](string_view s, bool is_f) -> string {
        string res;
        res.push_back(is_f ? 'L' : 'D');
        res.push_back(is_f ? 'U' : 'R');
        res.append(s);
        res.push_back(is_f ? 'R' : 'U');
        res.push_back(is_f ? 'D' : 'L');
        forr(ch, res) {
            if (ch == 'L') ch = 'R';
            else if (ch == 'R') ch = 'L';
            else if (ch == 'U') ch = 'D';
            else if (ch == 'D') ch = 'U';
        }
        reverse(all(res));
        return res;
    };

    string ans;
    auto [p1, p2] = get_path();
    ans.append(p1);
    ans.append(rev(p1, true));
    ans.append(p2);
    ans.append(rev(p2, false));
    cout << ans;
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
