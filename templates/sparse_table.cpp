//
// Created by aminjon on 8/27/22.
//

#include <bits/stdc++.h>

template <typename Node>
struct SparseTable {
  std::vector<std::vector<Node>> table;

  template <typename U>
  explicit SparseTable(const std::vector<U>& init_) { init(init_); }

  template <typename U>
  void init(const std::vector<U>& init_) {
    table.resize(init_.size());
    for (std::size_t i{}; i < init_.size(); ++i) {
      table[i].emplace_back(init_[i]);
    }
    for (std::size_t l{1}, j{}; 2 * l <= init_.size(); ++j, l <<= 1u) {
      for (std::size_t i{}; i + 2 * l <= init_.size(); ++i) {
        table[i].emplace_back(Node::unite(std::forward<Node>(table[i][j]),
                                          std::forward<Node>(table[i + l][j])));
      }
    }
  }

  [[nodiscard]] Node query(std::size_t l, std::size_t r) const {
    const auto b = std::__lg(r - l);
    return Node::unite(table[l][b], table[r - (1 << b)][b]);
  }
};

struct Node {
  int val = std::numeric_limits<int>::max();
  static Node unite(auto&& a, auto&& b) {
    return a.val < b.val ? a : b;
  }
};