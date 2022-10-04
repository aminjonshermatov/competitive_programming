#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

typedef long long ll;
typedef long double ld;

#define F first
#define S second
#define mk make_pair
#define pb push_back
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (ll)((x).size())

#define rep(i, a, b) for (ll i = (a); (i) < (b); ++(i))
#define forr(el, cont) for (auto &(el) : (cont))
#define read(k) ll k; cin >> k

#define IOS ios_base::sync_with_stdio(false); \
            cin.tie(nullptr);                 \
            cout.tie(nullptr);

template<typename T>
using V = vector<T>;

template<typename T = ll>
using ordered_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

[[maybe_unused]] mt19937 rnd(143);

const ll inf = 1e15;
const ll MOD = 1e9 + 7;
[[maybe_unused]] const ld pi = atan2(0, -1);
const ld eps = 1e-6;

// ========================================= PROBLEM =========================================

const ll MAX_N = 1e5 + 1;
V<ll> G[MAX_N];
ld dp[MAX_N];

void dfs(ll v, ll p) {
    bool has_any = false;

//    cout << v << endl;
    ld s = 0;
    for (auto u : G[v]) {
        if (u != p) {
            dfs(u, v);
            s += dp[u] + 1;
            has_any = true;
        }
    }

    if (has_any) dp[v] = s / (G[v].size() - (p != -1));
    else dp[v] = 0;
}

void solve() {
    read(N);

    fill(dp, dp + N, 0);

    rep (i, 1, N) {
        read(p);
        read(q);
        --p, --q;
        G[p].emplace_back(q);
        G[q].emplace_back(p);
    }


    dfs(0, -1);

    cout << setprecision(8) << dp[0] << '\n';
}

bool is_multi = false;

int main() {
    // auto start = chrono::steady_clock::now();

    IOS

    int T = 1;
    if (is_multi) cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        // cout << "Case #" << tc << ": ";
        solve();
        cout << '\n';
    }

    // auto finish = chrono::steady_clock::now();
    // auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(finish - start);
    // cerr << endl << "Time: " << elapsed_ms.count() << " ms\n";

    return 0;
}