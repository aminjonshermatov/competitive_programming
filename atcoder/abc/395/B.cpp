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

  std::vector g(n, std::string(n, '#'));
  for (auto x = 1; x <= n - x - 1; x += 2) {
    const auto y = n - x - 1;
    for (auto i = x, j = x; j <= y; g[i][j++] = '.') { }
    for (auto i = x, j = y; i <= y; g[i++][j] = '.') { }
    for (auto i = y, j = y; j >= x; g[i][j--] = '.') { }
    for (auto i = y, j = x; i >= x; g[i--][j] = '.') { }
  }
  for (auto i = 0; i < n; ++i) {
    Println(g[i]);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
