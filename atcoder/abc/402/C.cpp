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
  std::vector g(m, std::vector<int>{}), f(n, std::vector<int>{});
  std::vector deg(m, 0);
  for (int i = 0; i < m; ++i) {
    Scan(deg[i]);
    g[i].reserve(deg[i]);
    for (int j = 0; j < deg[i]; ++j) {
      int x;
      Scan(x);
      --x;
      g[i].emplace_back(x);
      f[x].emplace_back(i);
    }
  }

  std::vector vis(m, false);
  auto cur = 0;
  for (int i = 0; i < n; ++i) {
    int b;
    Scan(b);
    --b;

    for (auto j : f[b]) {
      if (--deg[j] == 0 && !vis[j]) {
        ++cur;
        vis[j] = true;
      }
    }
    Println(cur);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
