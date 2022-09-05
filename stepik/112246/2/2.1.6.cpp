//
// Created by aminjon on 9/5/22.
//
#include "bits/stdc++.h"

using namespace std;

auto solve() {
    int n; cin >> n;

    vector<vector<vector<char>>> G(n + 2, vector<vector<char>>(n + 2, vector<char>(n + 2, '#')));
    array<int, 3> start{-1,-1,-1};
    for (int h = 1; h <= n; ++h) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                cin >> G[h][i][j];
                if (G[h][i][j] == 'S') start = {h, i, j};
            }
        }
    }

    queue<array<int, 3>> q;
    vector<vector<vector<int>>> dist(n + 2, vector<vector<int>>(n + 2, vector<int>(n + 2, -1)));
    q.push(start);
    dist[start[0]][start[1]][start[2]] = 0;
    while (!q.empty()) {
        auto [h, i, j] = q.front(); q.pop();
        if (h == 1) {
            cout << dist[h][i][j] << '\n';
            return;
        }

        for (int dh = -1; dh <= 1; ++dh) {
            for (int di = -1; di <= 1; ++di) {
                for (int dj = -1; dj <= 1; ++dj) {
                    if (dh*dh + di*di + dj*dj == 1) {
                        auto nh = h + dh, ni = i + di, nj = j + dj;
                        if (G[nh][ni][nj] != '#') {
                            G[nh][ni][nj] = '#';
                            dist[nh][ni][nj] = dist[h][i][j] + 1;
                            q.push({nh, ni, nj});
                        }
                    }
                }
            }
        }
    }

    cout << -1;
}

auto main() -> int32_t {
    solve();
}