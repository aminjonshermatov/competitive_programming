#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;

auto solve() {
    int n;
    cin >> n;

    string s;
    cin >> s;

    auto res{0};

    bool foo{true};
    for (int i = 0; i < n; ++i) {
        if (s[i] == '0') {
            if (i > 0 and i + 1 < n) {
                res += static_cast<int>(s[i - 1] == '0');
                res += static_cast<int>(s[i + 1] == '0');
            } else if (i == 0) res += static_cast<int>(s[i - 1] == '0');
            else if (i + 1 < n) res += static_cast<int>(s[i + 1] == '0');
            s[i - 1] = s[i + 1] = '0';
        }
    }

    cout << max(res, 0) << '\n';
}

auto main() -> int {
    auto start = chrono::steady_clock::now();

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

    auto finish = chrono::steady_clock::now();
    auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(finish - start);
    // cerr << endl << "Time: " << elapsed_ms.count() << " ms\n";

    return 0;
}