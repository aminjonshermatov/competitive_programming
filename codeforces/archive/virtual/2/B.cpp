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

ll power(ll a, ll b) {
    ll p = 0;
    for (auto temp = a; temp > 0 && temp % b == 0; temp /= b, ++p) {}

    return p;
}

ll get_pow(pair<ll, ll> &p, bool is2) {
    return is2 ? p.F : p.S;
}

string getPath(vector<vector<ll>> &dp, vector<vector<pair<ll, ll>>> &M, bool is2) {
    const ll N = sz(dp);
    string s;
    for (ll i = N - 1, j = N - 1; i != 0 || j != 0;) {
        if (i > 0 && dp[i - 1][j] + get_pow(M[i][j], is2) == dp[i][j]) {
            s.push_back('D');
            --i;
        } else if (j > 0 && dp[i][j - 1] + get_pow(M[i][j], is2) == dp[i][j]) {
            s.push_back('R');
            --j;
        }
    }

    reverse(all(s));
    return s;
}

void solve() {
    read(N);

    vector<vector<pair<ll, ll>>> M(N, vector<pair<ll, ll>>(N));
    pair<ll, ll> zero{-1,-1};
    for (ll i = 0; i < N; ++i) {
        for (ll j = 0; j < N; ++j) {
            read(a);
            M[i][j] = mk(power(a, 2), power(a, 5));
            if (a == 0 && zero.F == -1) zero = {i, j};
        }
    }

    vector<vector<ll>> dp2(N, vector<ll>(N, inf)), dp5(N, vector<ll>(N, inf));
    dp2[0][0] = M[0][0].F;
    dp5[0][0] = M[0][0].S;

    rep (i, 0, N) {
        rep (j, 0, N) {
            if (i > 0) {
                dp2[i][j] = min(dp2[i][j], dp2[i - 1][j] + M[i][j].F);
                dp5[i][j] = min(dp5[i][j], dp5[i - 1][j] + M[i][j].S);
            }

            if (j > 0) {
                dp2[i][j] = min(dp2[i][j], dp2[i][j - 1] + M[i][j].F);
                dp5[i][j] = min(dp5[i][j], dp5[i][j - 1] + M[i][j].S);
            }
        }
    }

    ll res = min(dp2[N - 1][N - 1], dp5[N - 1][N - 1]);

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
        string path = res == dp2[N - 1][N - 1] ? getPath(dp2, M, true) : getPath(dp5, M, false);

        cout << res << '\n' << path << '\n';
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