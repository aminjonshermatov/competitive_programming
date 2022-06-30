#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;

    vector<string> table(n);
    for (auto &row : table) cin >> row;

    // {row: {char: vector Idxs}}
    unordered_map<int, unordered_map<char, vector<int>>> hMap;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) hMap[j][table[i][j]].push_back(i);
    }

    int res = 0;
    for (int i = 0; i < n; ++i) {
        for (int s = 0; s < m; ++s) {
            for (int e = s + 1; e < m; ++e) {
                if (table[i][s] == table[i][e]) {
                    auto container_ = hMap[s][table[i][s]];
                    for (auto it = upper_bound(container_.begin(), container_.end(), i);
                    it != container_.end();
                    ++it) {
                        if (*it < n && table[*it][e] == table[*it][s]) ++res;
                    }
                }
            }
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
    //cin >> T;
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