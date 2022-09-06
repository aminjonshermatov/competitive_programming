//
// Created by aminjon on 9/6/22.
//
#include "bits/stdc++.h"

using namespace std;

auto solve() {
    int n, m, r, c, x, y;
    cin >> n >> m >> r >> c >> x >> y;

    vector<vector<char>> G(n + 2, vector<char>(m + 2, '*'));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> G[i][j];
        }
    }

    queue<array<int, 4>> q;
    q.push({r, c, x, y});

    int ans = 0;
    while (!q.empty()) {
        auto [i, j, xx, yy] = q.front(); q.pop();

        if (G[i - 1][j] == '.') {
            G[i - 1][j] = '*';
            ++ans;
            q.push({i - 1, j, xx, yy});
        }
        if (G[i + 1][j] == '.') {
            G[i + 1][j] = '*';
            ++ans;
            q.push({i + 1, j, xx, yy});
        }

        if (G[i][j - 1] == '.' && xx > 0) {
            G[i][j - 1] = '*';
            ++ans;
            q.push({i, j - 1, xx - 1, yy});
        }

        if (G[i][j + 1] == '.' && yy > 0) {
            G[i][j + 1] = '*';
            ++ans;
            q.push({i, j + 1, xx, yy - 1});
        }
    }

    cout << ans << '\n';
}

auto main() -> int32_t {
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);

    solve();
}