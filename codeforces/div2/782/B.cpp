#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;

void solve() {
    int n, k;
    string s;
    cin >> n >> k >> s;

    vector<bool> counts(n, false);

    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '0') counts[i] = true;
    }

    k %= 2 * n;

    while (k) {
        for (int i = 0; i < s.size(); ++i) {
            if (counts[i]) {
                --k;

            }
        }
    }
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