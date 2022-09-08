//
// Created by aminjon on 9/8/22.
//
#include "bits/stdc++.h"

using namespace std;

auto solve() {
    int n, s, f; cin >> n >> s >> f;
    --s, --f;

    vector<vector<pair<int, int>>> G(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int w; cin >> w;
            if (w != -1 && i != j) G[i].emplace_back(w, j);
        }
    }

    set<pair<int, int>> ss;
    vector<int> dist(n, INT_MAX), pred(n, -1);

    ss.insert({0, s});
    dist[s] = 0;

    while (!ss.empty()) {
        auto [d, v] = *ss.begin();
        ss.erase(ss.begin());

        for (auto [w, u] : G[v]) {
            if (d + w < dist[u]) {
                if (auto it = ss.find({dist[u], u}); it != ss.end()) ss.erase(it);

                dist[u] = d + w;
                pred[u] = v;

                ss.insert({dist[u], u});
            }
        }
    }

    cout << (dist[f] == INT_MAX ? -1 : dist[f]) << '\n';
}

auto main() -> int32_t {
    solve();
}