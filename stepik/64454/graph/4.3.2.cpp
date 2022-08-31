//
// Created by aminjon on 8/31/22.
//
#include "bits/stdc++.h"

using namespace std;

const size_t MAX_N = 1001u;

vector<int> G[MAX_N];

auto main() -> int32_t {
    int n, m; cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int p, q; cin >> p >> q;

        G[p].emplace_back(q);
        G[q].emplace_back(p);
    }

    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        vector<bool> seen(n + 1, false);
        queue<pair<int, int>> q;
        seen[i] = true;
        q.push({i, 0});

        while (!q.empty()) {
            auto it = q.front(); q.pop();

            for (auto u : G[it.first]) {
                if (!seen[u]) {
                    if (u > i) ans += it.second + 1;
                    seen[u] = true;
                    q.push({u, it.second + 1});
                }
            }
        }
    }

    cout << ans << '\n';
}