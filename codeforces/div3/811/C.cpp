#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define f first
#define s second

#define ll int64_t
#define ull uint64_t
#define pll pair<ll, ll>
#define pull pair<ull, ull>

#define all(x) (x).begin(), (x).end()
#define sz(x) (ll)(x.size())
#define mk make_pair
#define pb push_back
#define eb emplace_back

#define rep(i, a, b) for (ll i = (a); i < (b); ++i)
#define read(T, k) T k; cin >> k

#define IOS ios_base::sync_with_stdio(false); \
            cin.tie(nullptr);                 \
            cout.tie(nullptr);

using namespace std;

void solve() {
    read(ll, ss);

    ll cur = 0, ans[10];
    rep(i, 0, 10) ans[i] = 0;

    for (ll c = 9, i = 9; ss > 0; --c) {
        if (c <= ss) {
            ans[i--] = c;
            ss -= c;
        }
    }

    ll i = 0;
    for (; ans[i] == 0 && i < 10; ++i) {}
    rep(t, i, 10) cout << ans[t];
    cout << '\n';
}

int main() {
    // auto start = chrono::steady_clock::now();

    IOS

    int T = 1;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        // cout << "Case #" << tc << ": ";
        solve();
        // cout << '\n';
    }

    // auto finish = chrono::steady_clock::now();
    // auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(finish - start);
    // cerr << endl << "Time: " << elapsed_ms.count() << " ms\n";

    return 0;
}