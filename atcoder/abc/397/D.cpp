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
  int64_t n;
  Scan(n);
  for (int64_t a = 1; a * a * a < n; ++a) {
    const auto [b, r] = std::lldiv(n, a);
    if (r != 0) {
      continue;
    }
    const auto d = static_cast<__int128>(b) * 12 - static_cast<__int128>(a) * a * 3;
    __int128 lo = 0, hi = 1E15;
    while (hi - lo > 1) {
      const auto mid = std::midpoint(lo, hi);
      (mid * mid <= d ? lo : hi) = mid;
    }
    if (lo * lo != d) {
      continue;
    }
    const auto dSqrt = static_cast<int64_t>(lo);
    const auto y = static_cast<__int128>((dSqrt - a * 3) / 6);
    const auto x = a + y;
    if (x > 0 && y > 0 && x * x * x - y * y * y == n) {
      Println(static_cast<int64_t>(x), static_cast<int64_t>(y));
      return;
    }
  }
  Println(-1);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
