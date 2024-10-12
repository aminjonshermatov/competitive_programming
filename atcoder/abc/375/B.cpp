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
  using ld = long double;
  ld ret = 0;
  int64_t x = 0, y = 0;
  for (int i = 0; i < n; ++i) {
    int64_t xx, yy;
    scan(xx, yy);
    const auto dx = x - xx;
    const auto dy = y - yy;
    ret += std::sqrt(dx * dx + dy * dy);
    x = xx, y = yy;
  }
  ret += std::sqrt(x * x + y * y);
  std::cout << std::fixed << std::setprecision(10) << ret << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}