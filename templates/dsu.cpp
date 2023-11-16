//
// Created by aminjon on 12/1/22.
//
#include <bits/stdc++.h>

struct Dsu {
  int n, components;
  std::vector<int> parent, rank;

  explicit Dsu(int n_) : n(n_), components(n), parent(n), rank(n, 1) {
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
    rank[pv] += rank[pu];
    --components;
    return true;
  }

  inline bool is_same(int u, int v) {
    assert(0 <= v && v < n);
    assert(0 <= u && u < n);
    return find(v) == find(u);
  }
};

struct DsuRollback {
  int n, components;
  std::vector<int> parent, rank;

  enum class UpdateType : uint8_t { kUpdateRank, kUpdateParent };
  std::vector<std::tuple<UpdateType, int, int>> history;

  explicit DsuRollback(int n_) : n(n_), components(n), parent(n), rank(n, 1) {
    iota(parent.begin(), parent.end(), 0);
  }

  inline int find(int v) {
    assert(0 <= v && v < n);
    if (parent[v] != v) {
      history.emplace_back(UpdateType::kUpdateParent, v, parent[v]);
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
    history.emplace_back(UpdateType::kUpdateParent, pu, parent[pu]);
    parent[pu] = pv;
    history.emplace_back(UpdateType::kUpdateRank, pv, rank[pv]);
    rank[pv] += rank[pu];
    --components;
    return true;
  }

  inline bool is_same(int u, int v) {
    assert(0 <= v && v < n);
    assert(0 <= u && u < n);
    return find(v) == find(u);
  }

  void rollback() {
    while (std::get<0>(history.back()) != UpdateType::kUpdateRank) {
      assert(!history.empty());
      auto [_, v, old_parent] = history.back();
      parent[v] = old_parent;
      history.pop_back();
    }
    assert(history.size() > 1);
    {
      auto [type, v, old_rank] = history.back();
      assert(type == UpdateType::kUpdateRank);
      history.pop_back();
      rank[v] = old_rank;
    }
    {
      auto [type, v, old_parent] = history.back();
      assert(type == UpdateType::kUpdateParent);
      history.pop_back();
      parent[v] = old_parent;
    }
    ++components;
  }
};