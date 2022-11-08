//
// Created by aminjon on 11/8/22.
//
#include <bits/stdc++.h>

using namespace std;

auto solve() {
    int N, M;
    cin >> N >> M;
    vector<set<int>> G(N + 1);
    for (int i = 0; i < M; ++i) {
        int p, q;
        cin >> p >> q;
        G[p].insert(q);
    }

    vector<int> order, used(N + 1, 0);
    order.reserve(N);
    auto dfs = [&](auto &self, int v) -> bool {
        used[v] = 1;

        for (auto u : G[v]) {
            if (used[u] == 0) {
                if (self(self, u)) return true;
            } else if (used[u] == 1) {
                return true;
            }
        }

        used[v] = 2;
        order.emplace_back(v);
        return false;
    };

    for (int v = N; v >= 1; --v) {
        if (!used[v] && dfs(dfs, v)) { cout << "cycle"; return; }
    }
    reverse(order.begin(), order.end());
    for (auto v : order) cout << v << ' ';
}

int main() {
    solve();
}