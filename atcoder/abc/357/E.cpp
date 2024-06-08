#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&&... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&&... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&&... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

void solve() {
  int n;
  scan(n);
  std::vector<std::vector<int>> g(n), ig(n);
  std::vector<int> as(n);
  for (int i = 0; i < n; ++i) {
    scan(as[i]);
    --as[i];
    g[i].emplace_back(as[i]);
    ig[as[i]].emplace_back(i);
  }

  std::vector<int> ord;
  std::vector used(n, false);
  auto dfsOrd = [&](auto&& self, const int v) -> void {
    used[v] = true;
    for (const auto u : g[v]) {
      if (!used[u]) {
        self(self, u);
      }
    }
    ord.emplace_back(v);
  };
  for (int v = 0; v < n; ++v) {
    if (!used[v]) {
      dfsOrd(dfsOrd, v);
    }
  }
  std::vector<int> comp(n);
  auto dfsComp = [&](auto&& self, const int v, const int c) -> void {
    comp[v] = c;
    used[v] = true;
    for (const auto u : ig[v]) {
      if (!used[u]) {
        self(self, u, c);
      }
    }
  };
  std::fill(used.begin(), used.end(), false);
  int curC = 0;
  for (const auto v : ord | std::views::reverse) {
    if (!used[v]) {
      dfsComp(dfsComp, v, curC++);
    }
  }
  g.assign(curC, {});
  std::vector<int> cnt(curC);
  for (int i = 0; i < n; ++i) {
    ++cnt[comp[i]];
    if (comp[i] != comp[as[i]]) {
      g[comp[i]].emplace_back(comp[as[i]]);
    }
  }
  used.assign(curC, false);
  ord.clear();
  for (int v = 0; v < curC; ++v) {
    if (!used[v]) {
      dfsOrd(dfsOrd, v);
    }
  }
  int64_t tot{};
  std::vector<int> dp(curC);
  for (const auto v : ord) {
    for (const auto u : g[v]) {
      dp[v] += dp[u];
    }
    dp[v] += cnt[v];
    tot += cnt[v] * 1LL * dp[v];
  }
  println(tot);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}