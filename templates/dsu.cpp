//
// Created by aminjon on 12/1/22.
//
#include <bits/stdc++.h>

struct Dsu {
  int n;
  std::vector<int> parent, rank;

  explicit Dsu(int n_) : n(n_), parent(n), rank(n, 1) {
    iota(parent.begin(), parent.end(), 0);
  }

  inline int find(int v) {
    assert(0 <= v && v < n);
    if (parent[v] != v) {
      parent[v] = find(parent[v]);
    }
    return parent[v];
  }

  bool merge(int u, int v) {
    assert(0 <= v && v < n);
    assert(0 <= u && u < n);
    auto pv = find(v);
    auto pu = find(u);
    if (pv == pu) {
      return false;
    }

    if (rank[pv] < rank[pu]) {
      std::swap(pv, pu);
    }
    parent[pu] = pv;
    rank[pv] += rank[pv] == rank[pu];
    return pv;
  }

  inline bool is_same(int u, int v) {
    assert(0 <= v && v < n);
    assert(0 <= u && u < n);
    return find(v) == find(u);
  }
};