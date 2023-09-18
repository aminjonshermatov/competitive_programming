//
// Created by aminjon on 9/4/22.
//
#include "bits/stdc++.h"

using namespace std;

auto solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> G(n + 2, vector<int>(m + 2, 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) cin >> G[i][j];
    }

    vector<vector<int>> len(n + 2, vector<int>(m + 2, -1));
    queue<array<int, 2>> q;
    len[1][1] = 0;
    q.push({1, 1});

    while (!q.empty()) {
        auto [i, j] = q.front(); q.pop();
        if (G[i][j] == 2) {
            cout << len[i][j] << '\n';
            return;
        }

        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                if (dy * dy + dx * dx == 1) {
                    auto ni = i;
                    auto nj = j;

                    while (true) {
                        if (G[ni][nj] == 2) break;
                        if (G[ni + dy][nj + dx] == 1) break;

                        ni += dy;
                        nj += dx;
                    }

                    if (len[ni][nj] == -1) {
                        len[ni][nj] = len[i][j] + 1;
                        q.push({ni, nj});
                    }
                }
            }
        }
    }

    cout << -1 << '\n';
}

auto main() -> int32_t {
    solve();
}