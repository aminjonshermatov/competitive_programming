//
// Created by aminjon on 9/5/22.
//
#include "bits/stdc++.h"

using namespace std;

auto solve() {
    int n, m; cin >> n >> m;

    if (n == 1) {
        cout << 0 << ' ' << 0 << '\n';
        return;
    }

    vector<int> whichSide(n);
    for (auto &a : whichSide) cin >> a;

    vector<vector<int>> G(n, vector<int>());
    for (int i = 0; i < m; ++i) {
        int p, q; cin >> p >> q;
        --p, --q;
        G[p].push_back(q);
        G[q].push_back(p);
    }

    vector<int> dist(n, -1), nodes(n, -1);

    deque<int> q;
    q.push_back(0);
    dist[0] =  0;
    nodes[0] = 1;

    while (!q.empty()) {
        auto from = q.front(); q.pop_front();

        for (auto to : G[from]) {
            auto fee = whichSide[from] == whichSide[to] ? 0 : 1;
            if (dist[to] == -1 || dist[to] > dist[from] + fee) {
                dist[to] = dist[from] + fee;
                nodes[to] = nodes[from] + 1;
                if (fee == 0) q.push_front(to);
                else q.push_back(to);
            }
        }
    }

    if (dist[n - 1] == -1) {
        cout << "impossible\n";
        return;
    }
    cout << dist[n - 1] << ' ' << nodes[n - 1] << '\n';
}

auto main() -> int32_t {
    solve();
}