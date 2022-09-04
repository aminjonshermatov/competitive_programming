//
// Created by aminjon on 9/3/22.
//
#include "bits/stdc++.h"

using namespace std;

auto main() -> int32_t {
    int x1, y1, x2, y2;
    char ch;
    cin >> ch; x1 = ch - 'a';
    cin >> ch; y1 = 8 - (ch - '0');
    cin >> ch; x2 = ch - 'a';
    cin >> ch; y2 = 8 - (ch - '0');

    function<bool(int, int)> isSafe;
    isSafe = [&](int i, int j) -> bool { return i >= 0 && i < 8 && j >= 0 && j < 8; };

    queue<array<int, 2>> q;
    array<int, 8> dy = {2,2,1,1,-1,-1,-2,-2};
    array<int, 8> dx = {-1,1,-2,2,-2,2,-1,1};
    array<array<array<int, 2>, 8>, 8> dist{};
    for (int i = 0; i < 8; ++i) fill(dist[i].begin(), dist[i].end(), array{INT_MAX, INT_MAX});

    q.push({y1, x1});
    dist[y1][x1][0] = 0;
    while (!q.empty()) {
        auto [i, j] = q.front(); q.pop();

        for (int k = 0; k < 8; ++k) {
            auto ii = i + dy[k];
            auto jj = j + dx[k];

            if (isSafe(ii, jj) && dist[ii][jj][0] == INT_MAX) {
                dist[ii][jj][0] = dist[i][j][0] + 1;
                q.push({ii, jj});
            }
        }
    }

    q.push({y2, x2});
    dist[y2][x2][1] = 0;
    while (!q.empty()) {
        auto [i, j] = q.front(); q.pop();
        if (dist[i][j][0] == dist[i][j][1]) {
            cout << dist[i][j][0] << '\n';
            return 0;
        }

        for (int k = 0; k < 8; ++k) {
            auto ii = i + dy[k];
            auto jj = j + dx[k];

            if (isSafe(ii, jj) && dist[ii][jj][1] == INT_MAX) {
                dist[ii][jj][1] = dist[i][j][1] + 1;
                q.push({ii, jj});
            }
        }
    }

    cout << -1 << '\n';
}