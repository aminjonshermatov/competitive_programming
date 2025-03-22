#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

void Solve() {
  int n;
  Scan(n);
  std::vector<std::vector<int>> g(n);
  for (int i = 0; i + 1 < n; ++i) {
    int u, v;
    Scan(u, v);
    --u, --v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }
  std::vector dep(n, 0), par(n, -1);
  auto dfs = [&](auto&& self, int v) -> void {
    for (const auto u : g[v]) {
      if (u != par[v]) {
        dep[u] = dep[v] + 1;
        par[u] = v;
        self(self, u);
      }
    }
  };
  dfs(dfs, 0);
  std::set<std::pair<int, int>> good;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (dep[i] % 2 != dep[j] % 2 && par[i] != j && par[j] != i) {
        good.emplace(i + 1, j + 1);
      }
    }
  }
  bool isMyTurn = good.size() % 2 == 1;
  std::cout << (isMyTurn ? "First" : "Second") << std::endl;
  for (;; isMyTurn ^= 1) {
    if (isMyTurn) {
      assert(!good.empty());
      const auto [u, v] = *good.begin();
      good.erase(good.begin());
      std::cout << u << ' ' << v << std::endl;
    } else {
      int i, j;
      Scan(i, j);

      if (i == -1 && j == -1) {
        break;
      }
      assert(std::clamp(i, 1, n) == i);
      assert(std::clamp(j, 1, n) == j);
      if (i > j) {
        std::swap(i, j);
      }
      auto it = good.find(std::pair(i, j));
      assert(it != good.end());
      good.erase(it);
    }
  }
}

int main() {
//  std::ios_base::sync_with_stdio(false);
//  std::cin.tie(nullptr);

  Solve();
}
