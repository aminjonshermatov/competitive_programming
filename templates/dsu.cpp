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

    while (v != parent[v]) {
      v = parent[v] = parent[parent[v]];
    }
    return v;
  }

  bool merge(int u, int v) {
    assert(0 <= u && u < n);
    assert(0 <= v && v < n);
    auto pu = find(u);
    auto pv = find(v);
    if (pu == pv) {
      return false;
    }

    if (rank[pu] < rank[pv]) {
      std::swap(pu, pv);
    }
    parent[pv] = pu;
    rank[pu] += rank[pv];
    --components;
    return true;
  }

  inline bool is_same(int u, int v) {
    assert(0 <= u && u < n);
    assert(0 <= v && v < n);
    return find(u) == find(v);
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
    while (v != parent[v]) {
      history.emplace_back(UpdateType::kUpdateParent, v, parent[v]);
      v = parent[v] = parent[parent[v]];
    }
    return v;
  }

  bool merge(int u, int v) {
    assert(0 <= u && u < n);
    assert(0 <= v && v < n);
    auto pu = find(u);
    auto pv = find(v);
    if (pu == pv) {
      return false;
    }

    if (rank[pu] < rank[pv]) {
      std::swap(pu, pv);
    }
    history.emplace_back(UpdateType::kUpdateParent, pv, parent[pv]);
    parent[pv] = pu;
    history.emplace_back(UpdateType::kUpdateRank, pu, rank[pu]);
    rank[pu] += rank[pv];
    --components;
    return true;
  }

  inline bool is_same(int u, int v) {
    assert(0 <= u && u < n);
    assert(0 <= v && v < n);
    return find(u) == find(v);
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

template <typename Node> struct DsuWeighted {
  int n, components;
  std::vector<int> parent, rank;
  std::vector<Node> weight;

  explicit DsuWeighted(int n_) : n(n_), components(n), parent(n), rank(n, 1), weight(n, Node()) {
    iota(parent.begin(), parent.end(), 0);
  }

  inline decltype(auto) find(int v) {
    assert(0 <= v && v < n);
    auto res = Node();

    while (v != parent[v]) {
      res = Node::unite(res, weight[v]);
      res = Node::unite(res, weight[parent[v]]);
      weight[v] = Node::unite(weight[v], weight[parent[v]]);
      v = parent[v] = parent[parent[v]];
    }
    return std::pair(v, res);
  }

  bool merge(int u, int v, Node w) {
    assert(0 <= u && u < n);
    assert(0 <= v && v < n);
    auto [pu, wu] = find(u);
    auto [pv, wv] = find(v);
    if (pu == pv) {
      return false;
    }

    if (rank[pu] < rank[pv]) {
      std::swap(pv, pu);
      std::swap(wv, wu);
      w = Node::inverse(w);
    }
    // U - V = w
    // weight[v] - weight[u] + ? = w
    // ? = weight[u] - weight[v] + w
    parent[pv] = pu;
    rank[pu] += rank[pv];
    weight[pv] = Node::unite(wu, Node::unite(Node::inverse(wv), w));
    --components;
    return true;
  }

  inline bool is_same(int u, int v) {
    assert(0 <= u && u < n);
    assert(0 <= v && v < n);
    return find(u).first == find(v).first;
  }
};

using i64 = int64_t;
struct Node {
  i64 val = 0;
  inline static Node unite(Node a, Node b) {
    return Node{a.val + b.val};
  }
  inline static Node inverse(Node a) {
    return Node{-a.val};
  }
  inline bool operator==(const Node &node) const noexcept {
    return val == node.val;
  }
};
