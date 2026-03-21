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

  std::vector g(n - 1, std::vector(n, int64_t{}));
  for (int i = 0; i + 1 < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      Scan(g[i][j]);
    }
  }
  dbg(g);

  for (int a = 0; a < n; ++a) {
    for (int b = a + 1; b < n; ++b) {
      for (int c = b + 1; c < n; ++c) {
        if (g[a][b] + g[b][c] < g[a][c]) {
          Println("Yes");
          return;
        }
      }
    }
  }
  Println("No");
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
