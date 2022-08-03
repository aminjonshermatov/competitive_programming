#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> w(n);
    for (auto &wi : w) cin >> wi;

    int a = 0, b = 0, res = 0, l = 0, r = n - 1;

    while (l < r) {
        if (a < b) {
            while (a < b and l < r) a += w[l++];

            if (a == b) res = l + n - r;
        }
        else {
            do {
                b += w[r--];
            } while (b < a and l < r);

            if (a == b) res = l + 1 + n - r + 1;
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