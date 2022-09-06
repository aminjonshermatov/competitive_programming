//
// Created by aminjon on 9/6/22.
//
#include "bits/stdc++.h"

using namespace std;

const size_t N = 1e4;
int seen[N];

auto solve() {
    int n, m; cin >> n >> m;

    memset(seen, 0, sizeof(int) * N);
    seen[n] = 1;

    queue<pair<int, int>> q;
    q.push({n, 0});

    while (!q.empty()) {
        int sz = (int)q.size();

        while (sz-- > 0) {
            auto [it, d] = q.front(); q.pop();
            if (it == m) {
                cout << d + 1;
                return ;
            }

            auto b = it / 1000, e = it % 10;
            auto new_ = it + 1000;
            if (b != 9 && seen[new_] == 0) {
                seen[new_] = 1;
                q.push({new_, d + 1});
            }
            new_ = it - 1;
            if (e != 1 && seen[new_] == 0) {
                seen[new_] = 1;
                q.push({new_, d + 1});
            }
            new_ = e * 1000 + it / 10;
            if (seen[new_] == 0) {
                seen[new_] = 1;
                q.push({new_, d + 1});
            }
            new_ = (it % 1000) * 10 + b;
            if (seen[new_] == 0) {
                seen[new_] = 1;
                q.push({new_, d + 1});
            }
        }
    }

    cout << -1 << '\n';
}

auto main() -> int32_t {
//    freopen("../input.txt", "r", stdin);
//    freopen("../output.txt", "w", stdout);

    solve();
}