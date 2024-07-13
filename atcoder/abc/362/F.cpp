#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("tree-vectorize")
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&& ... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

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

  std::vector<int> sub(n);
  auto dfsSz = [&](auto&& self, const int v, const int p) -> int {
    sub[v] = 1;
    for (auto u : g[v]) {
      if (u != p) {
        sub[v] += self(self, u, v);
      }
    }
    return sub[v];
  };
  auto dfsC = [&](auto&& self, const int v, const int p, const int desired) -> int {
    for (auto u : g[v]) {
      if (u != p && sub[u] >= desired) {
        return self(self, u, v, desired);
      }
    }
    return v;
  };
  const auto c = dfsC(dfsC, 0, -1, (dfsSz(dfsSz, 0, -1) + 1) / 2);
  
  std::vector<int> xs;
  auto dfs = [&](auto&& self, const int v, const int p) -> void {
    xs.emplace_back(v);
    for (auto&& u : g[v]) {
      if (u != p) {
        self(self, u, v);
      }
    }
  };
  for (auto u : g[c]) {
    dfs(dfs, u, c);
  }
  if (n % 2 == 0) {
    xs.emplace_back(c);
  }
  const auto m = n / 2;
  for (int i = 0; i < m; ++i) {
    println(xs[i] + 1, xs[i + m] + 1);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

#ifdef LOCAL
  freopen("../../input.txt", "r", stdin);
#endif

  solve();
}