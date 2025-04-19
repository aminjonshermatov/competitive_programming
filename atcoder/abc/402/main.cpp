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
  int n, m, a, b1, b2;
  Scan(n, m, a, b1, b2);

  auto norm = [m](const int64_t x) {
    return (x % m + m) % m;
  };

  int64_t ret = 0;
  for (int k = 0; k < n; ++k) {
    ret += norm(a * 1LL * k + b1) * norm(a * 1LL * k + b2);
  }
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  Scan(t);
  while (t-- > 0) {
    Solve();
  }
}
