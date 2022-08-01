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
    unordered_map<ll, ll> freq;
    priority_queue<ll, vector<ll>, greater<>> pq;

    rep(i, 0, n) {
        read(ll, k);
        ++freq[k];
        if (freq[k] == 1) pq.push(k);
    }

    while (pq.size() > 1 && pq.top() != 0) {
        cout << pq.size() << ' ' << pq.top() << '\n';
        auto t = pq.top(); pq.pop();
        auto newT = t + t % 10;
        if (t == newT) return;

        freq[newT] += freq[t];
        freq[t] = 0;
        if (pq.top() != newT) pq.push(newT);
    }

    cout << (pq.size() == 1 && freq[pq.top()] == n ? "YES" : "NO") << '\n';
}

int main() {
    // auto start = chrono::steady_clock::now();

    IOS

    freopen("output.txt","w",stdout);

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