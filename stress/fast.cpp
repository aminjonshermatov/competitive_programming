#include <bits/stdc++.h>

constexpr void scan(auto&&... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&&... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&&... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

auto solve() {
  int a, b;
  scan(a, b);
  println(a + b);
}

int main() {
  solve();
}