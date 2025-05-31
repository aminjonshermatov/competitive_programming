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
  int n, s;
  Scan(n, s);
  std::vector as(n + 1, 0);
  for (int i = 1; i <= n; ++i) {
    Scan(as[i]);
  }

  auto f = true;
  for (int i = 1; i <= n; ++i) {
    f &= as[i] - as[i - 1] <= s;
  }
  Println(f ? "Yes" : "No");
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
