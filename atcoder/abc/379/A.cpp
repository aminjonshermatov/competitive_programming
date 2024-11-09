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
  char a, b, c;
  scan(a, b, c);
  std::cout << b << c << a << ' ';
  std::cout << c << a << b << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}