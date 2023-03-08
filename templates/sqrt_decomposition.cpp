//
// Created by aminjon on 3/8/23.
//
#include <bits/stdc++.h>

using namespace std;

template <typename T, int K = 500> class sqrt_decomposition {
    int n;
    vector<T> nums;
    array<T, K> blocks;
public:
    template<typename U = T> explicit sqrt_decomposition(const vector<U> &A) : n(A.size()), nums(A) {
        assert(K * K >= n);
        fill(blocks.begin(), blocks.end(), 0);
        for (int i = 0; i < n; ++i) {
            blocks[i / K] += nums[i];
        }
    }

    void modify(int i, T v) {
        blocks[i / K] -= nums[i];
        nums[i] = v;
        blocks[i / K] += nums[i];
    }

    [[nodiscard]] T query(int r) const {
        T ans = 0;
        for (int i = 0; i < r / K; i++) ans += blocks[i];
        for (int i = (r / K) * K; i < r; i++) ans += nums[i];
        return ans;
    }

    [[nodiscard]] T query(int l, int r) const { // [l, r)
        assert(l < r);
        return query(r) - query(l);
    }
};