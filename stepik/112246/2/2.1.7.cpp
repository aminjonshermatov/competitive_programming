//
// Created by aminjon on 9/5/22.
//
#include "bits/stdc++.h"

using namespace std;

auto solve() {
    int n, m, y, x, Q;
    cin >> n >> m >> y >> x >> Q;
    --y, --x;

    function<bool(int, int)> isSafe;
    isSafe = [&](int i, int j) -> bool {
        return i >= 0 && i < n && j >= 0 && j < m;
    };

    int need = 0;
    vector<vector<int>> G(n, vector<int>(m, -1));
    for (int k = 0; k < Q; ++k) {
        int i, j; cin >> i >> j;
        if (isSafe(--i, --j)) {
            ++need;
            G[i][j] = 1;
            if (i == y && j == x) --need;
        }
    }

    array<int, 8> dy{2,2,1,1,-1,-1,-2,-2};
    array<int, 8> dx{-1,1,-2,2,-2,2,-1,1};

    int64_t ans = 0;
    queue<array<int, 3>> q;
    q.push({y, x, 0});
    G[y][x] = 0;

    while (!q.empty()) {
        auto [i, j, d] = q.front(); q.pop();

        for (int k = 0; k < 8; ++k) {
            auto ii = i + dy[k], jj = j + dx[k];

            if (isSafe(ii, jj) && G[ii][jj] != 0) {
                if (G[ii][jj] == 1) {
                    ans += d + 1;
                    --need;
                }
                G[ii][jj] = 0;
                q.push({ii, jj, d + 1});
            }
        }
    }

    cout << (need == 0 ? ans : -1) << '\n';
}

auto main() -> int32_t {
    solve();
}