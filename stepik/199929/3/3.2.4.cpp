//
// Created by aminjon on 11/8/22.
//
#include <bits/stdc++.h>

using namespace std;

using graph_t = vector<vector<int>>;

auto solve() {
    int N, M;
    cin >> N >> M;
    graph_t g_dir(N + 1), g_un_dir(N + 1);
    for (int i = 0; i < M; ++i) {
        int p, q;
        cin >> p >> q;
        g_dir[p].emplace_back(q);
        g_un_dir[p].emplace_back(q);
        g_un_dir[q].emplace_back(p);
    }

    vector<int> used(N + 1, 0);
    auto dfs = [&](auto &self, graph_t &g, int v) -> bool {
        used[v] = 1;

        for (auto u : g[v]) {
            if ((!used[u] && self(self, g, u)) || used[u] == 1) return true;
        }

        used[v] = 2;
        return false;
    };

    array<string, 2> ans{"NO", "NO"};
    for (int v = 1; v <= N; ++v) {
        if (!used[v] && dfs(dfs, g_dir, v)) { ans[0] = "YES"; break; }
    }
    fill(used.begin(), used.end(), 0);
    for (int v = 1; v <= N; ++v) {
        if (!used[v] && dfs(dfs, g_un_dir, v)) { ans[1] = "YES"; break; }
    }
    for (auto &s : ans) cout << s << '\n';
}

int main() {
    solve();
}