//
// Created by aminjon on 11/4/22.
//
#include <bits/stdc++.h>

using namespace std;

template<typename TWeight = int> struct Lca {
    int n, LG;
    vector<vector<pair<int, int>>> g;
    vector<vector<int>> up;
    int timer;
    vector<int> tin, tout;
    bool is_dfs_called;

    explicit Lca(int n_) : n(n_), g(n), up(n), timer(0), tin(n, -1), tout(n, -1), is_dfs_called(false) {
        LG = 31 - __builtin_clz(n);
        for (auto &r : up) r.resize(LG + 1, -1);
    }

    void add_edge(int u, int v, TWeight w = TWeight(0)) {
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    void dfs(int v = 0, int p = 0) {
        is_dfs_called = true;
        up[v][0] = p;
        for (int lg = 1; lg <= LG; ++lg) {
            up[v][lg] = up[up[v][lg - 1]][lg - 1];
        }

        tin[v] = timer++;
        for (auto [u, _] : g[v]) if (u != p) dfs(u, v);
        tout[v] = timer++;
    }

    [[nodiscard]] inline bool is_accessor(int u, int v) const {
        return tin[u] <= tin[v] && tout[v] <= tout[u];
    }

    [[nodiscard]] int operator()(int u, int v) const {
        assert(is_dfs_called);
        if (is_accessor(u, v)) return u;
        if (is_accessor(v, u)) return v;
        for (int lg = LG; ~lg; --lg) {
            if (!is_accessor(up[u][lg], v)) u = up[u][lg];
        }
        return up[u][0];
    }
};