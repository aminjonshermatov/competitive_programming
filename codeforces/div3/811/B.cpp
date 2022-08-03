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
    read(ll, n);

    vector<ll> a(n);
    rep(i, 0, n) cin >> a[i];

    unordered_set<ll> seen;
    for (ll i = n - 1; i >= 0; --i) {
        if (seen.count(a[i]) != 0) {
            cout << i + 1 << '\n';
            return;
        }
        seen.insert(a[i]);
    }

    cout << 0 << '\n';
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