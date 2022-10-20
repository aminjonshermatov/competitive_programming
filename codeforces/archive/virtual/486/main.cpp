#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

typedef long long ll;
typedef unsigned long long ull;
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

const ll max_n = 2e5 + 11;
const ll log_n = 40;
ll prev_[max_n][log_n];
ll dp[max_n][log_n];

void solve() {
    ull n;
    cin >> n;

    auto s = to_string(n);
    array<ll, 10> fr{};
    fill(all(fr), 0);
    forr(c, s) ++fr[c - '0'];

    if (fr[0] < 2
        && !(fr[2] > 0 && fr[5] > 0)
        && !(fr[5] > 0 && fr[0] > 0)
        && !(fr[7] > 0 && fr[5] > 0)) {
        cout << -1;
        return;
    }

    ll ans = INT_MAX;
    ll N = sz(s);
    ll i00 = N - 1;
    while (i00 >= 0 && s[i00] != '0') --i00;
    ll i01 = N - 1;
    while (i01 >= 0 && (s[i01] != '0' || i00 == i01)) --i01;
    if (i00 >= 0 && i01 >= 0) ans = min(ans, N - i00 - 1 + N - i01 - 2);

    ll i252 = N - 1;
    while (i252 >= 0 && s[i252] != '2') --i252;
    ll i255 = N - 1;
    while (i255 >= 0 && s[i255] != '5') --i255;
    if (i252 >= 0 && i255 >= 0) ans = min(ans, N - i255 - 1 + N - i252 - 2);

    ll i505 = i255;
    while (i505 >= 0 && (s[i505] != '5' || i505 >= i00)) --i505;
    if (i505 >= 0 && i00 >= 0) ans = min(ans, N - i00 - 1 + N - i505 - 2);

    ll i757 = N - 1;
    while (i757 >= 0 && (s[i757] != '7' || i757 >= i255)) --i757;
    if (i757 >= 0 && i255 >= 0) ans = min(ans, N - i255 - 1 + N - i757 - 2);

    cout << (ans == INT_MAX ? -1 : ans);
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
