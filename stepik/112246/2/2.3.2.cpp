//
// Created by aminjon on 9/19/22.
//
#include "bits/stdc++.h"

using namespace std;

auto solve() {
    int n; cin >> n;
    vector<int> W(n);
    for (auto &w : W) cin >> w;

    int m; cin >> m;
    vector<vector<int>> G(n);
    for (int i = 0; i < m; ++i) {
        int p, q; cin >> p >> q;
        --p, --q;
        G[p].emplace_back(q);
        G[q].emplace_back(p);
    }

    vector<int> dist(n, INT_MAX);
    dist[0] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.emplace(0, 0);

    while (!pq.empty()) {
        auto [w, v] = pq.top(); pq.pop();

        for (const auto u : G[v]) {
            if (w + W[v] < dist[u]) {
                pq.emplace(w + W[v], u);
                dist[u] = w + W[v];
            }
        }
    }

    cout << (dist[n - 1] == INT_MAX ? -1 : dist[n - 1]) << '\n';
}

auto main() -> int32_t {
    solve();
}