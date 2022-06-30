#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;

void solve() {
    int n; cin >> n;

    if (n == 1) cout << 1;
    else if (n < 4) cout << "NO SOLUTION";
    else if (n == 4) cout << "2 4 1 3";
    else {
        int lo = 2, hi = n;
        for (int i = 1; i <= n; ++i) {
            if (i & 1) cout << (i == n - 1 ? 1 : hi--) << ' ';
            else {
                cout << (i == n - 1 ? 1 : lo++) << ' ';
            }
        }
    }
    cout << '\n';
}

int main() {
    // auto start = chrono::steady_clock::now();

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T = 1;
//    cin >> T;
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