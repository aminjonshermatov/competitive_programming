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

#define all(x) (begin(x)), (end(x))
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

ll times[11];

void solve() {
    read(ll, n);
    read(ll, H);
    read(ll, M);
    ll t = H * 60 + M;

    rep(i, 0, n) {
        read(ll, h);
        read(ll, m);
        times[i] = h * 60 + m;
    }

    sort(times, times + n);

    auto lo = lower_bound(times, times + n, t);
    if (lo == times + n) lo = &times[0];

    ll ans = t > *lo ? 1440 - t + *lo : *lo - t;
    cout << ans / 60 << ' ' << ans % 60 << '\n';
}

int main() {
    // auto start = chrono::steady_clock::now();

    IOS

    read(int, T);
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