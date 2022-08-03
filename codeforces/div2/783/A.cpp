#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;

    if (n == 1 or m == 1) {
        if (n + m == 2) {
            cout << 0;
        } else {
            if (n == 1) {
                if (m == 2) cout << 1;
                else cout << -1;
            } else if (m == 1) {
                if (n == 2) cout << 1;
                else cout << -1;
            }
        }
    } else {
        int maxEl = max(n - 1, m - 1) << 1;
        if ((n & 1) == 0 xor (m & 1) == 0) --maxEl;
        cout << maxEl;
    }
    cout << '\n';
}

int main() {
    // auto start = chrono::steady_clock::now();

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

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