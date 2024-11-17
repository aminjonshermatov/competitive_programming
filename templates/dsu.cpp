//
// Created by aminjon on 12/1/22.
//
#include <bits/stdc++.h>

class DSU {
 public:
  explicit DSU(int n)
    : N_(n), Components(n), Parent_(n), Rank(n, 1)
  {
    std::iota(Parent_.begin(), Parent_.end(), 0);
  }

  [[nodiscard]] int Find(int v) {
    assert(std::clamp(v, 0, N_ - 1) == v);

    while (v != Parent_[v]) {
      v = Parent_[v] = Parent_[Parent_[v]];
    }
    return v;
  }

  bool Merge(int u, int v) {
    assert(std::clamp(u, 0, N_ - 1) == u);
    assert(std::clamp(v, 0, N_ - 1) == v);

    auto pu = Find(u);
    auto pv = Find(v);
    if (pu == pv) {
      return false;
    }

    if (Rank[pu] < Rank[pv]) {
      std::swap(pu, pv);
    }
    Parent_[pv] = pu;
    Rank[pu] += Rank[pv];
    --Components;
    return true;
  }

  [[nodiscard]] bool IsSame(int u, int v) noexcept {
    assert(std::clamp(u, 0, N_ - 1) == u);
    assert(std::clamp(v, 0, N_ - 1) == v);

    return Find(u) == Find(v);
  }

 public:
  int Components{0};
  std::vector<int> Rank;

 private:
  int N_{0};
  std::vector<int> Parent_;
};

struct DSURollback {
  int n, components;
  std::vector<int> parent, rank;

  enum class UpdateType : uint8_t { kUpdateRank, kUpdateParent };
  std::vector<std::tuple<UpdateType, int, int>> history;

  explicit DSURollback(int n_) : n(n_), components(n), parent(n), rank(n, 1) {
    std::iota(parent.begin(), parent.end(), 0);
  }

  [[nodiscard]] int find(int v) {
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

  [[nodiscard]] bool is_same(int u, int v) noexcept {
    assert(0 <= u && u < n);
    assert(0 <= v && v < n);
    return find(u) == find(v);
  }

  [[nodiscard]] std::size_t snapshot() const noexcept {
    return history.size();
  }

  void rollback(std::size_t time) {
    for (; history.size() > time; history.pop_back()) {
      if (history.size() > 1u && std::get<0>(history.back()) == UpdateType::kUpdateRank && std::get<0>(history[int(history.size()) - 2]) == UpdateType::kUpdateParent) {
        rank[std::get<1>(history.back())] = std::get<2>(history.back());
        history.pop_back();
        parent[std::get<1>(history.back())] = std::get<2>(history.back());
        ++components;
      } else if (std::get<0>(history.back()) == UpdateType::kUpdateRank) {
        rank[std::get<1>(history.back())] = std::get<2>(history.back());
      } else if (std::get<0>(history.back()) == UpdateType::kUpdateParent) {
        parent[std::get<1>(history.back())] = std::get<2>(history.back());
      }
    }
  }
};

template <typename Node> struct DSUWeighted {
  int n, components;
  std::vector<int> parent, rank;
  std::vector<Node> weight;

  explicit DSUWeighted(int n_) : n(n_), components(n), parent(n), rank(n, 1), weight(n, Node()) {
    std::iota(parent.begin(), parent.end(), 0);
  }

  [[nodiscard]] decltype(auto) find(int v) {
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

  [[nodiscard]] bool is_same(int u, int v) const {
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
