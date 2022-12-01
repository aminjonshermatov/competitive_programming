//
// Created by aminjon on 12/1/22.
//
#include <bits/stdc++.h>

#define all(x) begin(x), end(x)

using namespace std;

class DSU {
    vector<int> parent, rank;
public:
    explicit DSU(int n) {
        parent.resize(n);
        iota(all(parent), 0);
        rank.assign(n, 1);
    }

    auto find(int v) -> int {
        if (parent[v] != v) parent[v] = find(parent[v]);
        return parent[v];
    }

    auto merge(int v, int u) -> void {
        auto pv = find(v);
        auto pu = find(u);
        if (pv == pu) return;

        if (rank[pv] < rank[pu]) swap(pv, pu);
        parent[pu] = pv;
        if (rank[pv] == rank[pu]) ++rank[pv];
    }

    auto is_same(int v, int u) -> bool {
        return find(v) == find(u);
    }
};