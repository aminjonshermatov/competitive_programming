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
        for (auto idx = 0u; idx < n; ++idx) modify(idx, idx + 1, A[idx]);
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

template <typename T = int> struct fenwick_tree_2d_point_update_range_query {
    int n, m;
    vector<vector<T>> bit;

    explicit fenwick_tree_2d_point_update_range_query(int n_, int m_) : n(n_), m(m_), bit(n_, vector<T>(m_, T(0)))  { }

    template<typename U = T> explicit fenwick_tree_2d_point_update_range_query(const vector<vector<U>> &A) : n(A.size()), m(A[0].size()), bit(A.size(), vector<U>(A[0].size(), T(0))) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                add(i, j, A[i][j]);
            }
        }
    }

    auto add(int y, int x, T val) -> void {
        for (int i = y; i < n; i = i | (i + 1)) {
            for (int j = x; j < m; j = j | (j + 1)) {
                bit[i][j] += val;
            }
        }
    }

    [[nodiscard]] auto get(int y, int x) const -> T {
        T ret = T(0);
        for (int i = y; i >= 0; i = (i & (i + 1)) - 1) {
            for (int j = x; j >= 0; j = (j & (j + 1)) - 1) {
                ret += bit[i][j];
            }
        }
        return ret;
    }

    [[nodiscard]] auto get(int y1, int x1, int y2, int x2) const -> T { // [l, r)
        auto res = get(y2 - 1, x2 - 1);
        if (y1 > 0) res -= get(y1 - 1, x2 - 1);
        if (x1 > 0) res -= get(y2 - 1, x1 - 1);
        if (y1 > 0 && x1 > 0) res += get(y1 - 1, x1 - 1);
        return res;
    }

};

template <typename T = int> struct fenwick_tree_2d_range_update_point_query {
    int n, m;
    vector<vector<T>> bit;

    explicit fenwick_tree_2d_range_update_point_query(int n_, int m_) : n(n_), m(m_), bit(n_, vector<T>(m_, T(0)))  { }

    template<typename U = T> explicit fenwick_tree_2d_range_update_point_query(const vector<vector<U>> &A) : n(A.size()), m(A[0].size()), bit(A.size(), vector<U>(A[0].size(), T(0))) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                add(i, j, A[i][j]);
            }
        }
    }

    auto add(int y, int x, T val) -> void {
        for (int i = y; i < n; i = i | (i + 1)) {
            for (int j = x; j < m; j = j | (j + 1)) {
                bit[i][j] += val;
            }
        }
    }

    auto modify(int y1, int x1, int y2, int x2, T val) -> void { // [, r)
        add(y2, x2, val);
        add(y1, x1, val);
        add(y1, x2, -val);
        add(y2, x1, -val);
    }

    [[nodiscard]] auto get(int y, int x) const -> T {
        T ret = T(0);
        for (int i = y; i >= 0; i = (i & (i + 1)) - 1) {
            for (int j = x; j >= 0; j = (j & (j + 1)) - 1) {
                ret += bit[i][j];
            }
        }
        return ret;
    }

};