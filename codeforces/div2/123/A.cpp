#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;

auto solve() -> void {
    string s;
    cin >> s;

    unordered_map<char, bool> freq;
    bool res = true;

    for (const auto ch : s) {
        if (ch == 'R' or ch == 'G' or ch == 'B') {
            if ((ch == 'R' and not freq['r']) or (ch == 'G' and not freq['g']) or (ch == 'B' and not freq['b'])) res = false;
        } else {
            freq[ch] = true;
        }
    }

    cout << (res ? "YES" : "NO") << '\n';
}

auto main() -> int {
    auto start = chrono::steady_clock::now();

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
//        cout << "Case #" << tc << ": ";
        solve();
//        cout << '\n';
    }

    auto finish = chrono::steady_clock::now();
    auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(finish - start);
    // cerr << endl << "Time: " << elapsed_ms.count() << " ms\n";

    return 0;
}