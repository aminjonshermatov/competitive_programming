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

pair<ll, ll> helper(ll a) {
    ll two = 0, five = 0;
    for (auto temp = a; temp > 0 && (temp & 1) == 0; temp >>= 1, ++two) {}
    for (auto temp = a; temp > 0 && temp % 5 == 0; temp /= 5, ++five) {}

    return {two, five};
}

void solve() {
    read(N);

    vector<vector<ll>> M(N, vector<ll>(N));
    pair<ll, ll> zero{-1,-1};
    for (ll i = 0; i < N; ++i) {
        for (ll j = 0; j < N; ++j) {
            cin >> M[i][j];
            if (M[i][j] == 0 && zero.F == -1) {
                zero = {i, j};
            }
        }
    }

    vector<vector<pair<ll, ll>>> dp(N, vector<pair<ll, ll>>(N));
    dp[N - 1][N - 1] = {0, 0};
    for (ll i = N - 1, j = N - 2; j >= 0; --j) {
        auto [a2, a5] = helper(M[i][j]);
        dp[i][j] = {a2 + dp[i][j + 1].F, a5 + dp[i][j + 1].S};
    }

    for (ll i = N - 2, j = N - 1; i >= 0; --i) {
        auto [a2, a5] = helper(M[i][j]);
        dp[i][j] = {a2 + dp[i + 1][j].F, a5 + dp[i + 1][j].S};
    }

    for (ll i = N - 2; i >= 0; --i) {
        for (ll j = N - 2; j >= 0; --j) {
            auto [a2, a5] = helper(M[i][j]);
            auto [d2, d5] = dp[i + 1][j];
            auto [r2, r5] = dp[i][j + 1];

            if (min(a2 + d2, a5 + d5) < min(a2 + r2, a5 + r5)) dp[i][j] = {a2 + d2, a5 + d5};
            else dp[i][j] = {a2 + r2, a5 + r5};
        }
    }

    ll res = min(dp[0][0].F, dp[0][0].S);

    if (res > 1 && zero.F != -1) {
        cout << 1 << '\n';
        ll i = 0, j = 0;
        while (i != zero.F) {
            cout << 'D';
            ++i;
        }
        while (j != zero.S) {
            cout << 'R';
            ++j;
        }

        while (i != N - 1) {
            cout << 'D';
            ++i;
        }

        while (j != N - 1) {
            cout << 'R';
            ++j;
        }

    } else {
        ll i = 0, j = 0;
        vector<char> path;

        while (i != N - 1 || j != N - 1) {
            auto [a2, a5] = helper(M[i][j]);

            if (i + 1 < N && dp[i + 1][j].F + a2 == dp[i][j].F && dp[i + 1][j].S + a5 == dp[i][j].S) {
                // down
                path.push_back('D');
                ++i;
            } else if (j + 1 < N &&dp[i][j + 1].F + a2 == dp[i][j].F && dp[i][j + 1].S + a5 == dp[i][j].S) {
                path.push_back('R');
                ++j;
            } else {
                cout << i << ' ' << j << " bad\n";
                return;
            }
        }

        cout << res << '\n';
        for (auto ch : path) cout << ch;
        cout << '\n';
    }
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