//
// Created by aminjon on 8/31/22.
//
#include "bits/stdc++.h"

using namespace std;

auto main() -> int32_t {
    int n, m, p, q, x1, y1, x2, y2;
    cin >> m >> n >> p >> q >> x1 >> y1 >> x2 >> y2;

    function<bool(int, int)> isSafe;
    isSafe = [n, m](int i, int j) -> bool {
        return i > 0 && i <= n && j > 0 && j <= m;
    };

    vector<vector<bool>> seen(n + 1, vector<bool>(m + 1, false));
    queue<array<int, 3>> Q;
    Q.push({y1, x1, 0});
    while (!Q.empty()) {
        auto it = Q.front(); Q.pop();

        if (it[0] == y2 && it[1] == x2) {
            cout << it[2];
            return 0;
        }

        for (auto a : {-p, p}) {
            for (auto b : {-q, q}) {
                auto ii = it[0] + a;
                auto jj = it[1] + b;

                if (isSafe(ii, jj) && !seen[ii][jj]) {
                    seen[ii][jj] = true;
                    Q.push({ii, jj, it[2] + 1});
                }

                ii = it[0] + b;
                jj = it[1] + a;

                if (isSafe(ii, jj) && !seen[ii][jj]) {
                    seen[ii][jj] = true;
                    Q.push({ii, jj, it[2] + 1});
                }
            }
        }
    }

    cout << -1;
}