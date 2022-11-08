//
// Created by aminjon on 11/8/22.
//
#include <bits/stdc++.h>

using namespace std;

auto solve() {
    int N, M;
    cin >> N >> M;
    vector<set<int>> G(N);
    for (int i = 0; i < M; ++i) {
        int p, q;
        cin >> p >> q;
        G[p].insert(q);
    }

    vector<int> order, used(N, 0);
    order.reserve(2 * N);
    auto dfs = [&](auto &self, int v) -> void {
        order.emplace_back(v);
        used[v] = 1;

        for (auto u : G[v]) if (!used[u]) {
            self(self, u);
        }

        order.emplace_back(v);
    };

    for (int v = 0; v < N; ++v) {
        if (!used[v]) dfs(dfs, v);
    }
    for (auto v : order) cout << v << ' ';
}

int main() {
    solve();
}