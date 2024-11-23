#include <bits/stdc++.h>

constexpr void Scan(auto&&... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&&... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&&... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

auto Solve() {
  int a, b;
  Scan(a, b);
  Println(a + b);
}

int main() {
  Solve();
}