#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;

inline int hash_f(int a, int i, int j) {
    return (i * 207 + j) * 207 + static_cast<int>(a);
}

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> d(n, vector<int>(m));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) cin >> d[i][j];
    }

    unordered_map<int, int> cache;
    const function<int(int, int, int)> dfs = [&](int a, int i, int j) -> int {
        auto hash_ = hash_f(a, i, j);
        if (cache.count(hash_) > 0) return cache.at(hash_);
        if (i < 0 || i >= n || j < 0 || j >= m) return 0;

        int add_ = 0;
        if (a == 0) add_ = dfs(a, i - 1, j - 1);
        else if (a == 1) add_ = dfs(a, i - 1, j + 1);
        else if (a == 2) add_ = dfs(a, i + 1, j + 1);
        else if (a == 3) add_ = dfs(a, i + 1, j - 1);

        return cache[hash_] = d[i][j] + add_;
    };


    int res = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            res = max(res, d[i][j] + dfs(0, i - 1, j - 1) + dfs(1, i - 1, j + 1) + dfs(2, i + 1, j + 1) + dfs(3, i + 1, j - 1));
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