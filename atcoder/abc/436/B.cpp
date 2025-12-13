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
  std::vector g(n, std::vector(n, 0));
  int r = 0, c = (n - 1) / 2, k = 1;
  g[r][c] = k;
  dbg(g);
  for (int _ = 0; _ < n * n - 1; ++_) {
    auto f = false;
    {
      const auto nr = ((r + n - 1) % n + n) % n;
      const auto nc = ((c + 1) % n + n) % n;
      if (g[nr][nc] == 0) {
        g[r = nr][c = nc] = ++k;
        f = true;
      }
    }
    if (!f) {
      const auto nr = ((r + 1) % n + n) % n;
      const auto nc = c;
      if (g[nr][nc] == 0) {
        g[r = nr][c = nc] = ++k;
      }
    }
    dbg(g);
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      Print(g[i][j]);
    }
    Println();
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
