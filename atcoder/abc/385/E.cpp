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
  std::vector<int> deg(n);
  for (int i = 1; i < n; ++i) {
    int u, v;
    Scan(u, v);
    --u, --v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
    ++deg[u], ++deg[v];
  }
  for (int v = 0; v < n; ++v) {
    for (auto& u : g[v]) {
      u =  deg[u];
    }
    std::ranges::sort(g[v], std::greater{});
  }
  auto ret = 0;
  for (int v = 0; v < n; ++v) {
    for (std::size_t i{0}; i < g[v].size(); ++i) {
      ret = std::max<int>(ret, (i + 1) * g[v][i] + 1);
    }
  }
  Println(n - ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
