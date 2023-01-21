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

void solve() {
    int n; cin >> n;
    vector<int> A(n);
    forr(a, A) cin >> a;
    vector<string> adj(n);
    forr(a, adj) cin >> a;

    auto cmp = [](pll &lhs, pll &rhs) { return lhs.fi > rhs.fi || (lhs.fi == rhs.fi && lhs.se < rhs.se); };

    vector<vector<pll>> dp(n, vector<pll>(n, pair(inf, 0)));
    rep(i, n) {
        dp[i][i].fi = 0;
        dp[i][i].se = A[i];
    }
    rep(i, n) rep(j, n) if (adj[i][j] == 'Y') {
        pll temp = pair(1, 0ll + A[i] + A[j]);
        if (cmp(dp[i][j], temp)) dp[i][j] = temp;
    }

    rep(i, n) {
        rep(j, n) {
            rep(k, n) {
                pll temp = pair(dp[j][i].fi + dp[i][k].fi, dp[j][i].se + dp[i][k].se - A[i]);
                if (cmp(dp[j][k], temp)) dp[j][k] = temp;
            }
        }
    }

    int q; cin >> q;
    rep(_, q) {
        int u, v; cin >> u >> v, --u, --v;

        if (dp[u][v].fi == inf) {
            cout << "Impossible\n";
            continue;
        }
        cout << dp[u][v].fi << ' ' << dp[u][v].se << '\n';
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
