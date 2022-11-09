//
// Created by aminjon on 11/8/22.
//
#include <bits/stdc++.h>

using namespace std;

auto solve() {
    int N, M;
    cin >> N >> M;

    vector<vector<int>> g(N), gr(N);
    vector<int> out_deg(N, 0);
    for (int i = 0; i < M; ++i) {
        int p, q;
        cin >> p >> q;
        g[p - 1].emplace_back(q - 1);
        gr[q - 1].emplace_back(p - 1);
        ++out_deg[p - 1];
    }

    vector<bool> used(N, false);
    vector<int> order;
    order.reserve(N);
    auto top_sort = [&](auto &self, int v) -> void {
        used[v] = true;

        for (auto u : g[v]) if (!used[u]) self(self, u);
        order.emplace_back(v);
    };

    for (int v = 0; v < N; ++v) if (!used[v]) top_sort(top_sort, v);

    vector<int> comp(N, -1), p(N, -1);
    int cur_comp = 0;
    auto dfs = [&](auto &self, int v) -> void {
        comp[v] = cur_comp;
        p[cur_comp] = v;

        for (auto u : gr[v]) if (comp[u] == -1) self(self, u);
    };

    reverse(order.begin(), order.end());
    for (auto v : order) if (comp[v] == -1) dfs(dfs, v), ++cur_comp;
    used.assign(cur_comp, true);
    for (int v = 0; v < N; ++v) {
        for (auto u : g[v]) {
            if (comp[v] != comp[u]) used[comp[v]] = false;
        }
    }

    set<int> ans;
    for (int c = 0; c < cur_comp; ++c) if (used[c]) ans.insert(p[c]);
    cout << ans.size() << '\n';
    for (auto v : ans) cout << v + 1 << '\n';
}

int main() {
    solve();
}