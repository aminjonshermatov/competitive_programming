#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;

void solve() {
    int n;
    cin >> n;

    uint64_t hmap[11][11];
    for (auto &i : hmap) {
        for (auto &j : i) j = 0ull;
    }

    uint64_t res = 0;

    for (int k = 0; k < n; ++k) {
        char a, b;
        cin >> a >> b;

        for (int i = 0; i < 11; ++i) {
            if (b != 'a' + i and hmap[a - 'a'][i] > 0) {
                res += hmap[a - 'a'][i];
            }
        }

        for (int i = 0; i < 11 and a != b; ++i) {
            if (a != 'a' + i and hmap[b - 'a'][i] > 0) {
                res += hmap[b - 'a'][i];
            }
        }
        ++hmap[a - 'a'][b - 'a'];
        if (a != b) ++hmap[b - 'a'][a - 'a'];
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