//
// Created by aminjon on 3/11/23.
//
#include <bits/stdc++.h>

using i64 = int64_t;

const int BLOCK_SIZE = 500;

struct Query {
  int l, r, idx;
  bool operator<(const Query &other) const {
    return std::pair(l / BLOCK_SIZE, r) < std::pair(other.l / BLOCK_SIZE, other.r);
  }
};

void solve() {
  int n, q;
  std::cin >> n >> q;
  std::vector<i64> as(n);
  for (auto &a : as) {
    std::cin >> a;
  }
  std::vector<Query> queries(q);
  for (int i = 0; i < q; ++i) {
    int l, r;
    std::cin >> l >> r;
    --l, --r;
    queries[i] = Query{l, r, i};
  }

  sort(queries.begin(), queries.end());

  i64 cur = 0;
  std::vector<i64> cnt(1e6 + 1, 0);
  auto add = [&](i64 idx) -> void {
    cur -= cnt[as[idx]] * cnt[as[idx]] * as[idx];
    ++cnt[as[idx]];
    cur += cnt[as[idx]] * cnt[as[idx]] * as[idx];
  };
  auto rmv = [&](i64 idx) -> void {
    cur -= cnt[as[idx]] * cnt[as[idx]] * as[idx];
    --cnt[as[idx]];
    cur += cnt[as[idx]] * cnt[as[idx]] * as[idx];
  };

  std::vector<i64> ans(q);
  int cur_l = 0, cur_r = -1;
  for (auto [l, r, idx] : queries) {
    while (cur_l > l) add(--cur_l);
    while (cur_r < r) add(++cur_r);
    while (cur_l < l) rmv(cur_l++);
    while (cur_r > r) rmv(cur_r--);
    ans[idx] = cur;
  }

  for (auto &x : ans) {
    std::cout << x << '\n';
  }
}

// 3D Mo's algo
// https://gist.github.com/aminjonshermatov/8c34af802c075264b24615a971a0c09c