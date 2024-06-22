#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&&... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&&... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&&... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

using i64 = int64_t;

void solve() {
  int n;
  scan(n);
  std::vector<std::vector<int>> g(n);
  for (int i = 1; i < n; ++i) {
    int u, v;
    scan(u, v);
    --u, --v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }
  std::vector<int> as(n);
  for (auto&& a : as) {
    scan(a);
  }
  auto bs = as;
  std::ranges::sort(bs);
  bs.erase(std::ranges::unique(bs).begin(), bs.end());
  const auto m = static_cast<int>(bs.size());
  for (auto&& a : as) {
    a = static_cast<int>(std::distance(bs.begin(), std::ranges::lower_bound(bs, a)));
  }

  std::vector<int> subSzs(n);
  std::vector died(n, false);
  auto dfsSz = [&](auto&& self, const int v, const int p) -> int {
    subSzs[v] = 1;
    for (const auto u : g[v]) {
      if (u != p && !died[u]) {
        subSzs[v] += self(self, u, v);
      }
    }
    return subSzs[v];
  };
  auto dfsFindCentroid = [&](auto&& self, const int v, const int p, const int desired) -> int {
    for (const auto u : g[v]) {
      if (u != p && !died[u] && subSzs[u] >= desired) {
        return self(self, u, v, desired);
      }
    }
    return v;
  };
  i64 tot{};
  std::vector<i64> cnt(m), sum(m);
  std::vector<int> when_cnt(m), when_sum(m);
  int timer{1};
  auto dfsCalc = [&](auto&& self, const int v, const int p, const i64 curD, const bool doUpdate) -> void {
    if (doUpdate) {
      if (when_cnt[as[v]] != timer) {
        cnt[as[v]] = 0;
        when_cnt[as[v]] = timer;
      }
      ++cnt[as[v]];
      if (when_sum[as[v]] != timer) {
        sum[as[v]] = 0;
        when_sum[as[v]] = timer;
      }
      sum[as[v]] += curD;
      dbg("upd",v,curD);
    } else {
      if (when_cnt[as[v]] != timer) {
        cnt[as[v]] = 0;
        when_cnt[as[v]] = timer;
      }
      if (when_sum[as[v]] != timer) {
        sum[as[v]] = 0;
        when_sum[as[v]] = timer;
      }
      dbg("qry",v,curD,cnt[as[v]],sum[as[v]]);
      tot += curD * cnt[as[v]] + sum[as[v]];
    }
    for (const auto u : g[v]) {
      if (u != p && !died[u]) {
        self(self, u, v, curD + 1, doUpdate);
      }
    }
  };
  auto CD = [&](auto&& self, const int v, const int p) -> void {
    const auto c = dfsFindCentroid(dfsFindCentroid, v, p, dfsSz(dfsSz, v, p) / 2);
    died[c] = true;
    dbg(c);
    for (const auto u : g[c]) {
      if (!died[u]) {
        dfsCalc(dfsCalc, u, c, 1, false);
        dfsCalc(dfsCalc, u, c, 1, true);
      }
    }
    if (when_sum[as[c]] != timer) {
      when_sum[as[c]] = timer;
      sum[as[c]] = 0;
    }
    tot += sum[as[c]];
    ++timer;
    dbg(tot);
    for (const auto u : g[c]) {
      if (!died[u]) {
        self(self, u, c);
      }
    }
  };
  CD(CD, 0, -1);
  println(tot);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}