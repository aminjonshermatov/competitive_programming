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
    string s, t;
    cin >> s >> t;

    const int n(sz(s));
    const int m(sz(t));

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    vector<vector<char>> prv(n + 1, vector<char>(m + 1, '#'));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            dp[i][j] = max({(s[i - 1] == t[j - 1]) + dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]});
            if (dp[i][j] == (s[i - 1] == t[j - 1]) + dp[i - 1][j - 1]) {
                prv[i][j] = 'd';
            } else if (dp[i][j] == dp[i - 1][j]) {
                prv[i][j] = 'u';
            } else {
                prv[i][j] = 'l';
            }
        }
    }

    int mx = ninf;
    pair<int, int> cur(-1, -1);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (dp[i][j] > mx) {
                cur = pair(i, j);
                mx = dp[i][j];
            }
        }
    }

    string z;
    if (mx > 0) {
        assert(cur.fi != -1 && cur.se != -1);
        while (cur.fi != -1 && cur.se != -1 && prv[cur.fi][cur.se] != '#') {
            switch (prv[cur.fi][cur.se]) {
                case 'd': {
                    if (s[cur.fi - 1] == t[cur.se - 1]) z.pb(s[cur.fi - 1]);
                    --cur.fi;
                    --cur.se;
                    break ;
                }
                case 'u': {
                    --cur.fi;
                    break ;
                }
                case 'l': {
                    --cur.se;
                    break ;
                }
            }
        }
        reverse(all(z));
    }
    cout << z << '\n';
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
