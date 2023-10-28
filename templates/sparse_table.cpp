//
// Created by aminjon on 8/27/22.
//

#include <bits/stdc++.h>

template <typename T, typename Op = std::function<T(const T, const T)>> struct SparseTable {
  Op op;
  std::vector<std::vector<T>> table;
  std::vector<int> lg;

  template<typename U> auto init(const std::vector<U> &init_) -> void {
    table.assign(init_.size(), {});
    lg.resize(init_.size() + 1);
    lg[0] = -1;
    for (int i = 1; i <= init_.size(); ++i) {
      lg[i] = 31 - __builtin_clz(i);
    }
    for (auto i = 0u; i < init_.size(); ++i) {
      table[i] = {init_[i]};
    }
    for (auto l = 1u, j = 0u; 2 * l <= init_.size(); ++j, l <<= 1) {
      for (auto i = 0u; i + 2 * l <= init_.size(); ++i) {
        table[i].emplace_back(op(table[i][j], table[i + l][j]));
      }
    }
  }

  template<typename U> explicit SparseTable(const std::vector<U> &init_, Op &&op_) : op(op_) { init(init_); }

  [[nodiscard]] auto query(int l, int r) const -> int {
    assert(0 <= l && l < r && r <= table.size());
    const auto b = lg[r - l];
    return op(table[l][b], table[r - (1 << b)][b]);
  }
};