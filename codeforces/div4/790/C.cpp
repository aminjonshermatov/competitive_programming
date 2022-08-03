#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;

    vector<string> ss(n);
    for (int i = 0; i < n; ++i) cin >> ss[i];

    int res = INT_MAX;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;

            int cost_ = 0;
            for (int k = 0; k < m; ++k) cost_ += abs(ss[i][k] - ss[j][k]);

            res = min(res, cost_);
        }
    }

    cout << res << '\n';
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