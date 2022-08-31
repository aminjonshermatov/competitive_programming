//
// Created by aminjon on 8/31/22.
//
#include "bits/stdc++.h"

using namespace std;

const size_t MAX_N = 501u;

vector<int> G[MAX_N];
vector<int> res;
vector<bool> seen;

auto main() -> int32_t {
    int n, m; cin >> n >> m;

    seen.assign(n + 1, false);
    res.reserve(n);
    for (int i = 0; i < m; ++i) {
        int p, q; cin >> p >> q;

        G[p].emplace_back(q);
        G[q].emplace_back(p);
    }

    int x; cin >> x;
    queue<int> q;
    res.emplace_back(x);
    seen[x] = true;
    q.push(x);

    while (!q.empty()) {
        auto v = q.front(); q.pop();

        for (auto u : G[v]) {
            if (!seen[u]) {
                res.emplace_back(u);
                seen[u] = true;
                q.push(u);
            }
        }
    }

    for (auto it : res) cout << it << ' ';
    cout << '\n';
}