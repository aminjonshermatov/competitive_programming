//
// Created by aminjon on 8/27/22.
//

#include <bits/stdc++.h>

using namespace std;

auto Min = []<typename T>(const T &lhs, const T &rhs) -> T { return lhs < rhs ? lhs : rhs; };
auto Max = []<typename T>(const T &lhs, const T &rhs) -> T { return lhs > rhs ? lhs : rhs; };

template <typename T, typename Op> struct SparseTable {
  using value_type = T;
  Op op;
  vector<vector<T>> table;
  vector<int> lg;

  template<typename U = T> auto build(const vector<U> &A) -> void {
    table.assign(A.size(), {});
    lg.assign(A.size() + 1);
    lg[0] = -1;
    for (int i = 1; i <= A.size(); ++i) {
      lg[i] = 31 - __builtin_clz(i);
    }
    for (auto i = 0u; i < A.size(); ++i) table[i] = {A[i]};
    for (auto l = 1u, j = 0u; 2 * l <= A.size(); ++j, l <<= 1) {
      for (auto i = 0u; i + 2 * l <= A.size(); ++i) {
        table[i].emplace_back(op(table[i][j], table[i + l][j]));
      }
    }
  }

  SparseTable() = default;
  template<typename U = T> explicit SparseTable(const vector<U> &A) { build(A); }
  template<typename U = T> SparseTable(const vector<U> &A, Op &op_) : op(op_) { build(A); }

  [[nodiscard]] auto query(int l, int r) const -> int {
    assert(l < r);
    const auto b = lg[r - l];
    return op(table[l][b], table[r - (1 << b)][b]);
  }
};