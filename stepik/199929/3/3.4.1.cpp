//
// Created by aminjon on 11/8/22.
//
#include <bits/stdc++.h>

using namespace std;

auto solve() {
    int N;
    cin >> N;

    vector<vector<int>> g(N), gr(N);
    for (int v = 0; v < N; ++v) {
        int u;
        while (cin >> u && u != 0) {
            g[v].emplace_back(u - 1);
            gr[u - 1].emplace_back(v);
        }
    }

    vector<bool> used(N, false);
    vector<int> order, comp(N);
    order.reserve(N);
    int cur_comp = 0;
    auto top_sort = [&](auto &self, int v) -> void {
        used[v] = true;

        for (auto u : g[v]) if (!used[u]) self(self, u);
        order.emplace_back(v);
    };

    auto dfs = [&](auto &self, int v) -> void {
        used[v] = true;
        comp[v] = cur_comp;

        for (auto u : gr[v]) if (!used[u]) self(self, u);
    };

    for (int v = 0; v < N; ++v) if (!used[v]) top_sort(top_sort, v);
    reverse(order.begin(), order.end());
    fill(used.begin(), used.end(), false);
    for (auto v : order) if (!used[v]) ++cur_comp, dfs(dfs, v);

    for (int v = 0; v < N; ++v) if (comp[v] == comp[0]) cout << v + 1 << ' ';
    cout << '0';
}

int main() {
    solve();
}