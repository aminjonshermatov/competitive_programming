//
// Created by aminjon on 4/13/23.
//
#ifdef LOCAL
#include "constants.h"
#else
#define dbg(...) 42
#endif
#include <bits/stdc++.h>

constexpr int B = 800;

struct Query {
  int l, r, id;
  bool operator<(const Query &other) const {
    return std::pair(l / B, r) < std::pair(other.l / B, other.r);
  }
};

void solve(std::istream &in, std::ostream &out) {
  int n;
  in >> n;
  std::vector<int> ps(n), par(n, -1);
  for (int i = 0; i < n; ++i) {
    in >> ps[i];
    par[ps[i]] = i;
  }

  std::vector<int> comp(n, -1);
  std::iota(comp.begin(), comp.end(), 0);
  std::vector<std::vector<int>> nodes;

  std::vector<bool> used(n, false);
  for (auto V : ps) {
    if (used[V]) continue;
    std::queue<int> q;
    q.emplace(V);
    used[V] = true;
    auto c = int(nodes.size());
    nodes.emplace_back();
    while (!q.empty()) {
      auto v = q.front();
      q.pop();
      comp[v] = c;
      nodes.back().emplace_back(v);
      if (!used[ps[v]]) {
        q.emplace(ps[v]);
        used[ps[v]] = true;
      }
    }
  }

  int q;
  in >> q;
  std::vector<Query> qs(q);
  for (int i = 0; i < q; ++i) {
    in >> qs[i].l >> qs[i].r;
    qs[i].id = i;
  }
  std::sort(qs.begin(), qs.end());

  const auto m = (n + B) / B;
  std::vector<int> comp_cnt(n, 0), nodes_cnt(n + 1, 0), blk_nodes_cnt(m, 0);
  auto add = [&](int v) -> void {
    if (++comp_cnt[comp[v]] == 1) {
      for (auto u : nodes[comp[v]]) {
        if (++nodes_cnt[u] == 1) {
          ++blk_nodes_cnt[u / B];
        }
      }
    }
  };
  auto rmv = [&](int v) -> void {
    if (--comp_cnt[comp[v]] == 0) {
      for (auto u : nodes[comp[v]]) {
        if (--nodes_cnt[u] == 0) {
          --blk_nodes_cnt[u / B];
        }
      }
    }
  };
  auto mex = [&]() -> int {
    int ib = 0;
    for (; ib < m; ++ib) {
      if (blk_nodes_cnt[ib] != B) {
        break;
      }
    }
    for (int i = ib * B; i <= n; ++i) {
      if (nodes_cnt[i] == 0) {
        return i;
      }
    }
    assert(false);
  };

  std::vector<int> ans(q);
  int cur_l = 0, cur_r = -1;
  for (auto [l, r, idx] : qs) {
    while (cur_l > l) add(ps[--cur_l]);
    while (cur_r < r) add(ps[++cur_r]);
    while (cur_l < l) rmv(ps[cur_l++]);
    while (cur_r > r) rmv(ps[cur_r--]);
    ans[idx] = mex();
  }

  for (auto &x : ans) {
    out << x << '\n';
  }
}

int main() {
  auto in = std::ifstream(constants::DATA_IN);
  auto out = std::ofstream(constants::FAST_OUT);
  solve(in, out);

  return 0;
}
