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
  int x, y;
  Scan(x, y);
  using Ld = long double;

  Ld p = 0.;
  for (int a = 1; a <= 6; ++a) {
    for (int b = 1; b <= 6; ++b) {
      p += (a + b) >= x || std::abs(a - b) >= y;
    }
  }
  std::cout << std::fixed << std::setprecision(10) << p / 36 << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
