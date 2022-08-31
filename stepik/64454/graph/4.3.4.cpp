//
// Created by aminjon on 8/31/22.
//
#include "bits/stdc++.h"

using namespace std;

auto main() -> int32_t {
    int n, m; cin >> n >> m;
    const int mx_n = 2 * n + 1;
    const int mx_m = 2 * m + 1;
    cin.ignore(1);
    vector<string> G(2 * n + 1);
    vector<vector<array<bool, 4>>> seen(n, vector<array<bool, 4>>(m, {false, false, false, false}));

    function<bool(int, int)> isSafe;
    isSafe = [&](int i, int j) -> bool {
        return i >= 0 && i < mx_n && j >= 0 && j < mx_m;
    };

    for (auto &l : G) getline(cin, l);

    vector<array<int, 2>> S;
    for (int i = 1; i < 2 * n + 1; i += 2) {
        for (int j = 1; j < 2 * m + 1; j += 2) {
            if (G[i][j] == 'S') S.push_back({i, j});
        }
    }

    /*
     * 0 - left
     * 1 - bottom
     * 2 - right
     * 3 - top
    */
    vector<array<int, 2>> n2c;
    for (auto &s : S) {
        queue<array<int, 3>> q;

        {
            int i = s[0], j = s[1];
            if (G[i][j + 1] == '|' && G[i][j - 1] != '|' && isSafe(i, j - 2)) {
                seen[i/2][j/2][0] = true;
                q.push({i, j - 2, 0});
            }
            if (G[i - 1][j] == '-' && G[i + 1][j] != '-' && isSafe(i + 2, j)) {
                seen[i/2][j/2][1] = true;
                q.push({i + 2, j, 1});
            }
            if (G[i][j - 1] == '|' && G[i][j + 1] != '|' && isSafe(i, j + 2)) {
                seen[i/2][j/2][2] = true;
                q.push({i, j + 2, 2});
            }
            if (G[i + 1][j] == '-' && G[i - 1][j] != '-' && isSafe(i - 2, j)) {
                seen[i/2][j/2][3] = true;
                q.push({i - 2, j, 3});
            }
        }

        while (!q.empty()) {
            auto it = q.front(); q.pop();

            int i = it[0], j = it[1];
            if (G[i][j] == 'D') n2c.push_back({i, j});

            if (G[i][j + 1] == '|' && G[i][j - 1] != '|' && isSafe(i, j - 2) && !seen[i/2][(j - 2)/2][0]) {
                seen[i/2][(j - 2)/2][0] = true;
                q.push({i, j - 2, 0});
            }
            if (G[i - 1][j] == '-' && G[i + 1][j] != '-' && isSafe(i + 2, j) && !seen[(i + 2)/2][j/2][1]) {
                seen[(i + 2)/2][j/2][1] = true;
                q.push({i + 2, j, 1});
            }
            if (G[i][j - 1] == '|' && G[i][j + 1] != '|' && isSafe(i, j + 2) && !seen[i/2][(j + 2)/2][2]) {
                seen[i/2][(j + 2)/2][2] = true;
                q.push({i, j + 2, 2});
            }
            if (G[i + 1][j] == '-' && G[i - 1][j] != '-' && isSafe(i - 2, j) && !seen[(i - 2)/2][j/2][3]) {
                seen[(i - 2)/2][j/2][3] = true;
                q.push({i - 2, j, 3});
            }

            switch (it[2]) {
                case 0: {
                    if (G[i][j - 1] != '|' && isSafe(i, j - 2) && !seen[i/2][(j - 2)/2][0]) {
                        seen[i/2][(j - 2)/2][0] = true;
                        q.push({i, j - 2, 0});
                    }
                    break;
                }
                case 1: {
                    if (G[i + 1][j] != '-' && isSafe(i + 2, j) && !seen[(i + 2)/2][j/2][1]) {
                        seen[(i + 2)/2][j/2][1] = true;
                        q.push({i + 2, j, 1});
                    }
                    break;
                }
                case 2: {
                    if (G[i][j + 1] != '|' && isSafe(i, j + 2) && !seen[i/2][(j + 2)/2][2]) {
                        seen[i/2][(j + 2)/2][2] = true;
                        q.push({i, j + 2, 2});
                    }
                    break;
                }
                case 3: {
                    if (G[i - 1][j] != '-' && isSafe(i - 2, j) && !seen[(i - 2)/2][j/2][3]) {
                        seen[(i - 2)/2][j/2][3] = true;
                        q.push({i - 2, j, 3});
                    }
                    break;
                }
            }
        }
    }

    for (int i = 1; i < 2 * n + 1; i += 2) {
        for (int j = 1; j < 2 * m + 1; j += 2) {
            if (G[i][j] == 'D') G[i][j] = ' ';
        }
    }

    for (auto &c : n2c) G[c[0]][c[1]] = 'D';

    for (auto &l : G) cout << l << '\n';
}