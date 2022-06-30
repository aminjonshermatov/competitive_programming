#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;

void solve() {
    int n;
    string s;
    cin >> n >> s;

    int i = 0;
    while (i < n) {
        int r = 0, b = 0;
        while (i < n and s[i] != 'W') {
            if (s[i] == 'R') ++r;
            else ++b;
            ++i;
        }

        if (r + b == 1 or ((r > 0 ^ b > 0) and (r == 0 or b == 0))) {
            cout << "NO" << '\n';
            return;
        }
        ++i;
    }

    cout << "YES" << '\n';
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