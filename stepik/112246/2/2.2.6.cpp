//
// Created by aminjon on 9/7/22.
//
#include "bits/stdc++.h"

using namespace std;

auto solve() {
    int n, m; cin >> n >> m;
    vector<string> G(n);

    cin.ignore(1);
    pair<int, int> start, end;
    for (int i = 0; i < n; ++i) {
        getline(cin, G[i]);

        for (int j = 0; j < m; ++j) {
            if (G[i][j] == 'S') start = {i, j};
            else if (G[i][j] == 'F') end = {i, j};
        }
    }

    vector<vector<array<int, 4>>> dist(n, vector<array<int, 4>>(m, {-1,-1,-1,-1}));
    // 0-left, 1-top, 2-right, 3-down

    queue<array<int, 3>> q;
    for (int i = 0; i < 4; ++i) {
        dist[start.first][start.second][i] = 0;
        q.push({start.first, start.second, i});
    }

    while (!q.empty()) {
        auto [i, j, dir] = q.front(); q.pop();

        if (i == end.first && j == end.second) {
            cout << dist[i][j][dir] << '\n';
            return;
        }

        switch (dir) {
            case 0: {
                if (G[i][j - 1] != 'X' && dist[i][j - 1][0] == -1) {
                    dist[i][j - 1][0] = dist[i][j][0] + 1;
                    q.push({i, j - 1, 0});
                }

                if (G[i - 1][j] != 'X' && dist[i - 1][j][1] == -1) {
                    dist[i - 1][j][1] = dist[i][j][0] + 1;
                    q.push({i - 1, j, 1});
                }

                break;
            }
            case 1: {
                if (G[i - 1][j] != 'X' && dist[i - 1][j][1] == -1) {
                    dist[i - 1][j][1] = dist[i][j][1] + 1;
                    q.push({i - 1, j, 1});
                }

                if (G[i][j + 1] != 'X' && dist[i][j + 1][2] == -1) {
                    dist[i][j + 1][2] = dist[i][j][1] + 1;
                    q.push({i, j + 1, 2});
                }

                break;
            }
            case 2: {
                if (G[i][j + 1] != 'X' && dist[i][j + 1][2] == -1) {
                    dist[i][j + 1][2] = dist[i][j][2] + 1;
                    q.push({i, j + 1, 2});
                }

                if (G[i + 1][j] != 'X' && dist[i + 1][j][3] == -1) {
                    dist[i + 1][j][3] = dist[i][j][2]+ 1;
                    q.push({i + 1, j, 3});
                }

                break;
            }
            case 3: {
                if (G[i + 1][j] != 'X' && dist[i + 1][j][3] == -1) {
                    dist[i + 1][j][3] = dist[i][j][3]+ 1;
                    q.push({i + 1, j, 3});
                }

                if (G[i][j - 1] != 'X' && dist[i][j - 1][0] == -1) {
                    dist[i][j - 1][0] = dist[i][j][3] + 1;
                    q.push({i, j - 1, 0});
                }

                break;
            }
            default:
                cout << "wrong case;\n";
        }
    }

    cout << -1 << '\n';
}

auto main() -> int32_t {
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);

    solve();
}