// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

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
    auto remove = [&](i64 idx) -> void {
        auto c = cnt[A[idx]];
        cur -= c * (c - 1) * (c - 2) / 6;
        c = --cnt[A[idx]];
        cur += c * (c - 1) * (c - 2) / 6;
    };

    vector<i64> ans(q);
    int cur_l = 0, cur_r = -1;
    for (auto [l, r, idx] : queries) {
        while (cur_l > l) {
            cur_l--;
            add(cur_l);
        }
        while (cur_r < r) {
            cur_r++;
            add(cur_r);
        }
        while (cur_l < l) {
            remove(cur_l);
            cur_l++;
        }
        while (cur_r > r) {
            remove(cur_r);
            cur_r--;
        }
        ans[idx] = cur;
    }

    for (auto &x : ans) cout << x << '\n';
}

bool is_multi = false;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T = 1;
    if (is_multi) cin >> T;
    for (int tc = 1; tc <= T; ++tc) solve();

    return 0;
}
