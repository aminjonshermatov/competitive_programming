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

const ll MAX_N = 1e2 + 3;
const ll MAX_S = 1e5 + 3;

bool dp[MAX_N][MAX_S];

void solve() {
    read(N);
    vector<ll> A(N);
    ll max_ = 0;
    forr (a, A) {
        cin >> a;
        max_ = max(max_, a);
    }

    rep (i, 0, MAX_N) {
        rep (j, 0, MAX_S) dp[i][j] = false;
    }

    dp[0][0] = true;
    ll max_s = max_ * N;
    rep (i, 1, N + 1) {
        rep (s, 0, max_s + 1) {
            dp[i][s] = dp[i - 1][s];
            if (s >= A[i - 1] && dp[i - 1][s - A[i - 1]]) dp[i][s] = true;
        }
    }

    set<ll> uniq;
    rep (s, 1, max_s + 1)
        if (dp[N][s]) uniq.insert(s);

    cout << uniq.size() << '\n';
    forr (a, uniq) cout << a << ' ';
    cout << '\n';
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