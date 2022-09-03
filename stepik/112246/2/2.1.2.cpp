//
// Created by aminjon on 9/3/22.
//
#include "bits/stdc++.h"

using namespace std;

auto main() -> int32_t {
    int n, x1, y1, x2, y2;
    cin >> n >> x1 >> y1 >> x2 >> y2;
    function<bool(int, int)> isSafe;
    isSafe = [&](int i, int j) -> bool { return i > 0 && i <= n && j > 0 && j <= n; };
    array<int, 8> dy = {2, 2, 1, 1, -1, -1, -2, -2};
    array<int, 8> dx = {1, -1, 2, -2, 2, -2, 1, -1};

    vector<vector<int>> used(n + 1, vector<int>(n + 1, 0));
    queue<pair<int, int>> q;
    q.push({y1, x1});
    used[y1][x1] = 1;

    int ans = 0;
    while (!q.empty()) {
        int sz = (int)q.size();

        while (sz-- > 0) {
            auto [y, x] = q.front(); q.pop();
            if (y == y2 && x == x2) {
                cout << ans << '\n';
                return 0;
            }

            for (int i = 0; i < 8; ++i) {
                auto yy = y + dy[i];
                auto xx = x + dx[i];

                if (isSafe(yy, xx) && used[yy][xx] == 0) {
                    used[yy][xx] = 1;
                    //cout << yy << ' ' << xx << '\n';
                    q.push({yy, xx});
                }
            }
        }

        ++ans;
    }

    cout << ans << '\n';
}