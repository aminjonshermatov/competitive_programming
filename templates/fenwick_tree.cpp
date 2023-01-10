//
// Created by aminjon on 8/27/22.
//
#include <bits/stdc++.h>

using namespace std;

template <typename T = int> struct fenwick_tree {
    int n;
    vector<T> bit;

    explicit fenwick_tree(int n_) : n(n_), bit(n_, T(0))  { }

    template<typename U = T> explicit fenwick_tree(const vector<U> &A) : n(A.size()), bit(A.size(), T(0)) {
        for (auto idx = 0u; idx < n; ++idx) modify(idx, A[idx]);
    }

    auto modify(int idx, T val) -> void {
        for (; idx < n; idx = idx | (idx + 1)) bit[idx] += val;
    }

    [[nodiscard]] auto get(int idx) const -> T {
        T ret = T(0);
        for (; idx >= 0; idx = (idx & (idx + 1)) - 1) ret += bit[idx];
        return ret;
    }

    [[nodiscard]] auto get(int l, int r) const -> T { // [l, r)
        return get(r - 1) - get(l - 1);
    }

};

template <typename T = int> struct fenwick_tree_range_update_point_query {
    int n;
    vector<T> bit;

    explicit fenwick_tree_range_update_point_query(int n_) : n(n_), bit(n_, T(0))  { }

    template<typename U = T> explicit fenwick_tree_range_update_point_query(const vector<U> &A) : n(A.size()) , bit(A.size(), T(0)) {
        for (auto idx = 0u; idx < n; ++idx) add(idx, A[idx]);
    }

    auto add(int idx, T val) -> void {
        for (; idx < n; idx = idx | (idx + 1)) bit[idx] += val;
    }

    auto modify(int l, int r, T val) -> void { // [, r)
        add(l, val);
        add(r, -val);
    }

    [[nodiscard]] auto get(int idx) const -> T {
        T ret = T(0);
        for (; idx >= 0; idx = (idx & (idx + 1)) - 1) ret += bit[idx];
        return ret;
    }

};