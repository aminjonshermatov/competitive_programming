#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&&... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&&... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&&... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

void solve() {
  int score = 0;
  for ([[maybe_unused]] auto&& _ : std::views::iota(0, 9)) {
    int x;
    scan(x);
    score += x;
  }
  for ([[maybe_unused]] auto&& _ : std::views::iota(0, 8)) {
    int x;
    scan(x);
    score -= x;
  }
  println(std::max(0, score + 1));
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}