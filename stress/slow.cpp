#include <bits/stdc++.h>

constexpr void scan(auto&&... args) noexcept { (std::cin >> ... >> args); }

auto slow() {
  int a, b;
  scan(a, b);
  std::println("{}", a + b);
}

int main() {
  slow();
}