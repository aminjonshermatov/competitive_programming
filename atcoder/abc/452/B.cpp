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
  std::vector g(n, std::string(m, '.'));
  for (int i = 0; i < n; ++i) {
    g[i][0] = g[i][m - 1] = '#';
  }
  for (int j = 0; j < m; ++j) {
    g[0][j] = g[n - 1][j] = '#';
  }
  for (int i = 0; i < n; ++i) {
    Println(g[i]);
  }
  Println();
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
