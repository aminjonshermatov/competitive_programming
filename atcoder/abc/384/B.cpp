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
  auto isOk = [&](int r, int d) {
    if (d == 1) {
      return std::clamp(r, 1600, 2799) == r;
    }
    assert(d == 2);
    return std::clamp(r, 1200, 2399) == r;
  };
  int n, r;
  Scan(n, r);
  for (int i = 0; i < n; ++i) {
    int d, a;
    Scan(d, a);
    if (isOk(r, d)) {
      r += a;
    }
  }
  Println(r);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
