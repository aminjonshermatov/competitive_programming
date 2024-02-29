//
// Created by aminjon on 8/27/22.
//

#include <bits/stdc++.h>

template <typename Node> struct SparseTable {
  std::vector<std::vector<Node>> table;
  std::vector<int> lg;

  template <typename U> explicit SparseTable(const std::vector<U>& init_) { init(init_); }

  template <typename U> auto init(const std::vector<U>& init_) -> void {
    table.assign(init_.size(), {});
    lg.resize(init_.size() + 1);
    lg[0] = -1;
    for (int i = 1; i <= init_.size(); ++i) {
      lg[i] = 31 - __builtin_clz(i);
    }
    for (auto i = 0u; i < init_.size(); ++i) {
      table[i].push_back({init_[i]});
    }
    for (auto l = 1u, j = 0u; 2 * l <= init_.size(); ++j, l <<= 1) {
      for (auto i = 0u; i + 2 * l <= init_.size(); ++i) {
        table[i].emplace_back(Node::unite(table[i][j], table[i + l][j]));
      }
    }
  }

  [[nodiscard]] decltype(auto) query(int l, int r) const {
    const auto b = lg[r - l];
    return Node::unite(table[l][b], table[r - (1 << b)][b]);
  }
};

struct Node {
  int val = std::numeric_limits<int>::max();
  static Node unite(const Node& a, const Node& b) {
    return a.val < b.val ? a : b;
  }
};