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
  int m, d;
  Scan(m, d);

  auto f = false;
  if (m == 1 && d == 7) {
    f = true;
  } else if (m == 3 && d == 3) {
    f = true;
  } else if (m == 5 && d == 5) {
    f = true;
  } else if (m == 7 && d == 7) {
    f = true;
  } else if (m == 9 && d == 9) {
    f = true;
  }
  Println(f ? "Yes" : "No");
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
