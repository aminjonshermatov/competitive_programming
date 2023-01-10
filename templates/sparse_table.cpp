//
// Created by aminjon on 8/27/22.
//

#include <bits/stdc++.h>

using namespace std;

auto Min = []<typename T>(const T &lhs, const T &rhs) -> T { return lhs < rhs ? lhs : rhs; };
auto Max = []<typename T>(const T &lhs, const T &rhs) -> T { return lhs > rhs ? lhs : rhs; };

template <typename T, typename Op> struct sparse_table {
    using value_type = T;
    Op op;
    vector<vector<T>> table;

    template<typename U = T> auto build(const vector<U> &A) -> void {
        table.assign(A.size(), {});
        for (auto i = 0u; i < A.size(); ++i) table[i] = {A[i]};
        for (auto l = 1u, j = 0u; 2 * l <= A.size(); ++j, l <<= 1) {
            for (auto i = 0u; i + 2 * l <= A.size(); ++i) {
                table[i].emplace_back(op(table[i][j], table[i + l][j]));
            }
        }
    }

    sparse_table() = default;
    template<typename U = T> explicit sparse_table(const vector<U> &A) { build(A); }
    template<typename U = T> sparse_table(const vector<U> &A, Op &op_) : op(op_) { build(A); }

    [[nodiscard]] auto get(int l, int r) const -> int {
        assert(l < r);
        const auto b = 31 - __builtin_clz(r - l);
        return op(table[l][b], table[r - (1 << b)][b]);
    }
};