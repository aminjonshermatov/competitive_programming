//
// Created by aminjon on 3/11/23.
//
#include <bits/stdc++.h>

using namespace std;

using i64 = ::int64_t;

const int BLOCK_SIZE = 500;

struct Query {
    int l, r, idx;
    bool operator<(const Query &other) const {
        return pair(l / BLOCK_SIZE, r) < pair(other.l / BLOCK_SIZE, other.r);
    }
};

void solve() {
    int n, q; cin >> n >> q;
    vector<i64> A(n);
    for (auto &a : A) cin >> a;
    vector<Query> queries(q);
    for (int i = 0; i < q; ++i) {
        int l, r; cin >> l >> r, --l, --r;
        queries[i] = Query{l, r, i};
    }

    sort(queries.begin(), queries.end());

    i64 cur = 0;
    vector<i64> cnt(1e6 + 1, 0);
    auto add = [&](i64 idx) -> void {
        auto c = cnt[A[idx]];
        cur -= c * (c - 1) * (c - 2) / 6;
        c = ++cnt[A[idx]];
        cur += c * (c - 1) * (c - 2) / 6;
    };
    auto rmv = [&](i64 idx) -> void {
        auto c = cnt[A[idx]];
        cur -= c * (c - 1) * (c - 2) / 6;
        c = --cnt[A[idx]];
        cur += c * (c - 1) * (c - 2) / 6;
    };

    vector<i64> ans(q);
    int cur_l = 0, cur_r = -1;
    for (auto [l, r, idx] : queries) {
        while (cur_l > l) add(--cur_l);
        while (cur_r < r) add(++cur_r);
        while (cur_l < l) rmv(cur_l++);
        while (cur_r > r) rmv(cur_r--);
        ans[idx] = cur;
    }

    for (auto &x : ans) cout << x << '\n';
}