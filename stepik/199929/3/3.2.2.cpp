//
// Created by aminjon on 11/8/22.
//
#include <bits/stdc++.h>

using namespace std;

auto solve() {
    int N, M;
    cin >> N >> M;
    vector<vector<int>> G(N + 1);
    for (int i = 0; i < M; ++i) {
        int p, q;
        cin >> p >> q;
        G[p].emplace_back(q);
    }

    vector<int> order, used(N + 1, 0);
    order.reserve(N);
    auto dfs = [&](auto &self, int v) -> void {
        used[v] = 1;

        for (auto u : G[v]) if (!used[u]) {
            self(self, u);
        }

        order.emplace_back(v);
    };

    for (int v = 1; v <= N; ++v) {
        if (!used[v]) dfs(dfs, v);
    }
    reverse(order.begin(), order.end());
    for (auto v : order) cout << v << ' ';
}

int main() {
    solve();
}