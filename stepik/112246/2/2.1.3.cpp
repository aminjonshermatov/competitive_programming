//
// Created by aminjon on 9/3/22.
//
#include "bits/stdc++.h"

using namespace std;

auto main() -> int32_t {
    int n, m; cin >> n >> m;

    vector<vector<int>> G(n, vector<int>(m)), res(n, vector<int>(m, INT_MAX));
    vector<pair<int, int>> poss;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> G[i][j];
            if (G[i][j] != 0) poss.emplace_back(i, j), res[i][j] = 0;
        }
    }
    queue<pair<int, int>> q;
    array<int, 5> dk = {1,0,-1,0,1};
    function<bool(int, int)> isSafe;
    isSafe = [&](int i, int j) -> bool { return i >= 0 && i < n && j >= 0 && j < m; };

    for (auto [y, x] : poss) {
        q.push({y, x});

        while (!q.empty()) {
            auto [i, j] = q.front(); q.pop();

            for (int k = 0; k < 4; ++k) {
                auto ii = i + dk[k];
                auto jj = j + dk[k + 1];

                if (isSafe(ii, jj)
                && G[ii][jj] == 0
                && res[ii][jj] > res[i][j] + abs(i - ii) + abs(j - jj)) {
                    res[ii][jj] = res[i][j] + abs(i - ii) + abs(j - jj);
                    q.push({ii, jj});
                }
            }
        }
    }

    for (auto [i, j] : poss) res[i][j] = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << res[i][j] << ' ';
        }
        cout << '\n';
    }
}