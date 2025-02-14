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
  std::vector<int> as(n);
  for (int i = 0; i < n; ++i) {
    Scan(as[i]);
  }

  auto lo = 0, hi = n / 2 + 1;
  while (hi - lo > 1) {
    const auto mid = std::midpoint(lo, hi);
    auto ok = true;
    for (auto i = 0; i < mid; ++i) {
      ok &= as[i] * 2 <= as[n - mid + i];
    }
    (ok ? lo : hi) = mid;
  }
  Println(lo);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
