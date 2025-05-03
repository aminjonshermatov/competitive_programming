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
  int n, m;
  Scan(n, m);
  std::vector<std::vector<int>> g(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    Scan(u, v);
    --u, --v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }

  if (std::ranges::any_of(g, [](auto& vs) { return vs.size() != 2; })) {
    Println("No");
    return;
  }
  std::vector vis(n, false);
  auto dfs = [&](auto&& self, int v, int p) -> bool {
    if (vis[v]) {
      return v == 0;
    }
    vis[v] = true;
    for (auto u : g[v]) {
      if (u != p) {
        if (vis[u]) {
          return u == 0;
        } else {
          return self(self, u, v);
        }
      }
    }
    return false;
  };
  Println(dfs(dfs, 0, -1) && std::ranges::all_of(vis, std::identity{}) ? "Yes" : "No");
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
