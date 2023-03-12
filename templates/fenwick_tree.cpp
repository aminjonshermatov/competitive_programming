//
// Created by aminjon on 8/27/22.
//
#include <bits/stdc++.h>

using namespace std;

template <typename T = int> struct FenwickTreePointUpdateRangeQuery {
    int n;
    vector<T> bit;

    FenwickTreePointUpdateRangeQuery() = default;
    explicit FenwickTreePointUpdateRangeQuery(int n_) : n(n_), bit(n_, T(0))  { }
    template<typename U = T> explicit FenwickTreePointUpdateRangeQuery(const vector<U> &A) : n(A.size()), bit(A.size(), T(0)) {
        for (auto idx = 0u; idx < n; ++idx) modify(idx, A[idx]);
    }

    void init(int n_) {
        n = n_;
        bit.assign(n, T(0));
    }

    auto modify(int idx, T val) -> void {
        for (; idx < n; idx = idx | (idx + 1)) bit[idx] += val;
    }

    [[nodiscard]] auto query(int idx) const -> T {
        T ret = T(0);
        for (; idx >= 0; idx = (idx & (idx + 1)) - 1) ret += bit[idx];
        return ret;
    }

    [[nodiscard]] auto query(int l, int r) const -> T { // [l, r)
        return query(r - 1) - query(l - 1);
    }

};

template <typename T = int> struct FenwickTreeRangeUpdatePointQuery {
    int n;
    vector<T> bit;

    FenwickTreeRangeUpdatePointQuery() = default;
    explicit FenwickTreeRangeUpdatePointQuery(int n_) : n(n_), bit(n_, T(0))  { }
    template<typename U = T> explicit FenwickTreeRangeUpdatePointQuery(const vector<U> &A) : n(A.size()) , bit(A.size(), T(0)) {
        for (auto idx = 0u; idx < n; ++idx) modify(idx, idx + 1, A[idx]);
    }

    void init(int n_) {
        n = n_;
        bit.assign(n, T(0));
    }

    auto modify(int idx, T val) -> void {
        for (; idx < n; idx = idx | (idx + 1)) bit[idx] += val;
    }

    auto modify(int l, int r, T val) -> void { // [, r)
        modify(l, val);
        modify(r, -val);
    }

    [[nodiscard]] auto query(int idx) const -> T {
        T ret = T(0);
        for (; idx >= 0; idx = (idx & (idx + 1)) - 1) ret += bit[idx];
        return ret;
    }

};

template <typename T = int> struct FenwickTreeRangeUpdateRangeQuery {
    int n;
    vector<T> bitA, bitB;

    FenwickTreeRangeUpdateRangeQuery() = default;
    explicit FenwickTreeRangeUpdateRangeQuery(int n_) : n(n_), bitA(n_, T(0)), bitB(n_, T(0))  { }
    template<typename U = T> explicit FenwickTreeRangeUpdateRangeQuery(const vector<U> &A) : n(A.size()) , bitA(A.size(), T(0)), bitB(A.size(), T(0)) {
        for (auto idx = 0u; idx < n; ++idx) modify(idx, idx + 1, A[idx]);
    }

    void init(int n_) {
        n = n_;
        bitA.assign(n, T(0));
        bitB.assign(n, T(0));
    }

    auto modify(vector<T> &bit, int idx, T val) -> void {
        for (; idx < n; idx = idx | (idx + 1)) bit[idx] += val;
    }

    auto modify(int l, int r, T val) -> void { // [, r)
        modify(bitA, l, val);
        modify(bitA, r, -val);
        modify(bitB, l, val * (l - 1));
        modify(bitB, r, -val * (r - 1));
    }

    [[nodiscard]] auto query(const vector<T> &bit, int idx) const -> T {
        T ret = T(0);
        for (; idx >= 0; idx = (idx & (idx + 1)) - 1) ret += bit[idx];
        return ret;
    }

    [[nodiscard]] auto prefix_query(int idx) const -> T {
        return query(bitA, idx) * idx - query(bitB, idx);
    }

    [[nodiscard]] auto query(int l, int r) const -> T {
        return prefix_query(r - 1) - prefix_query(l - 1);
    }
    [[nodiscard]] auto query(int idx) const -> T {
        return prefix_query(idx) - prefix_query(idx - 1);
    }

};

template <typename T = int> struct FenwickTree2DPointUpdateRangeQuery {
    int n, m;
    vector<vector<T>> bit;

    FenwickTree2DPointUpdateRangeQuery() = default;
    explicit FenwickTree2DPointUpdateRangeQuery(int n_, int m_) : n(n_), m(m_), bit(n_, vector<T>(m_, T(0)))  { }
    template<typename U = T> explicit FenwickTree2DPointUpdateRangeQuery(const vector<vector<U>> &A) : n(A.size()), m(A[0].size()), bit(A.size(), vector<U>(A[0].size(), T(0))) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                add(i, j, A[i][j]);
            }
        }
    }

    void init(int n_, int m_) {
        n = n_;
        m = m_;
        bit.assign(n, vector<T>(m, T(0)));
    }

    auto modify(int y, int x, T val) -> void {
        for (int i = y; i < n; i = i | (i + 1)) {
            for (int j = x; j < m; j = j | (j + 1)) {
                bit[i][j] += val;
            }
        }
    }

    [[nodiscard]] auto query(int y, int x) const -> T {
        T ret = T(0);
        for (int i = y; i >= 0; i = (i & (i + 1)) - 1) {
            for (int j = x; j >= 0; j = (j & (j + 1)) - 1) {
                ret += bit[i][j];
            }
        }
        return ret;
    }

    [[nodiscard]] auto query(int y1, int x1, int y2, int x2) const -> T { // [l, r)
        auto res = query(y2 - 1, x2 - 1);
        if (y1 > 0) res -= query(y1 - 1, x2 - 1);
        if (x1 > 0) res -= query(y2 - 1, x1 - 1);
        if (y1 > 0 && x1 > 0) res += query(y1 - 1, x1 - 1);
        return res;
    }

};

template <typename T = int> struct FenwickTree2DRangeUpdatePointQuery {
    int n, m;
    vector<vector<T>> bit;

    FenwickTree2DRangeUpdatePointQuery() = default;
    explicit FenwickTree2DRangeUpdatePointQuery(int n_, int m_) : n(n_), m(m_), bit(n_, vector<T>(m_, T(0)))  { }
    template<typename U = T> explicit FenwickTree2DRangeUpdatePointQuery(const vector<vector<U>> &A) : n(A.size()), m(A[0].size()), bit(A.size(), vector<U>(A[0].size(), T(0))) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                add(i, j, A[i][j]);
            }
        }
    }

    void init(int n_, int m_) {
        n = n_;
        m = m_;
        bit.assign(n, vector<T>(m, T(0)));
    }

    auto modify(int y, int x, T val) -> void {
        for (int i = y; i < n; i = i | (i + 1)) {
            for (int j = x; j < m; j = j | (j + 1)) {
                bit[i][j] += val;
            }
        }
    }

    auto modify(int y1, int x1, int y2, int x2, T val) -> void { // [, r)
        modify(y2, x2, val);
        modify(y1, x1, val);
        modify(y1, x2, -val);
        modify(y2, x1, -val);
    }

    [[nodiscard]] auto query(int y, int x) const -> T {
        T ret = T(0);
        for (int i = y; i >= 0; i = (i & (i + 1)) - 1) {
            for (int j = x; j >= 0; j = (j & (j + 1)) - 1) {
                ret += bit[i][j];
            }
        }
        return ret;
    }

};