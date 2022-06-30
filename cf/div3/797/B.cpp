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
#define read(t, k) t k; cin >> k

#define IOS ios_base::sync_with_stdio(false); \
            cin.tie(nullptr);                 \
            cout.tie(nullptr);

using namespace std;

void solve() {
    read (ll, n);
    vector<ll> A(n), B(n);
    for (auto &a : A) cin >> a;
    for (auto &b : B) cin >> b;

    ll x = -1, y = -1;
    bool ok = true;
    rep(i, 0, n) {
        if (A[i] < B[i]) ok = false;

        if (A[i] > 0 && B[i] > 0) {
            if (x == -1) x = A[i] - B[i];
            else if (A[i] - B[i] != x) ok = false;
        } else if (A[i] > 0 || B[i] > 0) {
            if (y == -1) y = A[i] - B[i];
            else y = max(y, A[i] - B[i]);
        }
        if (!ok) break;
    }

    if (ok && y != - 1 && x != -1 && y > x) ok = false;

    cout << (ok ? "YES" : "NO") << '\n';
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