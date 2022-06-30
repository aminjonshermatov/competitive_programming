#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;

auto solve() -> void {
    vector<pair<int, int>> V(3);

    for (int i = 0; i < 3; ++i) cin >> V[i].first >> V[i].second;

    sort(V.begin(), V.end(), [](const auto &lhs, const auto &rhs) -> bool { return lhs.second < rhs.second; });

    if (V[1].second == V[2].second) {
        cout << fixed << setprecision(10) << sqrt(pow(V[2].first - V[1].first, 2) + pow(V[2].second - V[1].second, 2));
    } else {
        cout << 0;
    }
    cout << '\n';
}

auto main() -> int {
    auto start = chrono::steady_clock::now();

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T;
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