//
// Created by aminjon on 11/8/22.
//
#include <bits/stdc++.h>

using namespace std;

using graph_t = vector<vector<int>>;

auto solve() {
    int N, M;
    cin >> N >> M;

    graph_t g(N), gr(N);
    for (int i = 0; i < M; ++i) {
        int p, q;
        cin >> p >> q;
        --p, --q;
        g[p].emplace_back(q);
        gr[q].emplace_back(p);
    }

    vector<bool> used(N, false);
    vector<int> order;
    order.reserve(N);
    auto dfs1 = [&](auto &self, int v) -> void {
        used[v] = true;

        for (auto u : g[v]) if (!used[u]) {
            self(self, u);
        }
        order.emplace_back(v);
    };

    int comp = -1;
    vector<int> ans(N);
    auto dfs2 = [&](auto &self, int v) -> void {
        used[v] = true;
        ans[v] = comp;

        for (auto u : gr[v]) if (!used[u]) {
            self(self, u);
        }
    };

    for (int v = 0; v < N; ++v) if (!used[v]) dfs1(dfs1, v);
    fill(used.begin(), used.end(), false);
    reverse(order.begin(), order.end());
    for (auto v : order) if (!used[v]) ++comp, dfs2(dfs2, v);

    vector<int> dict(comp + 1, -1);
    int k = 0;
    for (auto n : ans) if (dict[n] == -1) dict[n] = ++k;

    cout << k << '\n';
    for (auto n : ans) cout << dict[n] << ' ';
}

int main() {
    solve();
}