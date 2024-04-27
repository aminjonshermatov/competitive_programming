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
  int n;
  scan(n);
  std::vector<std::string> A(n), B(n);
  for (auto&& r : A) {
    scan(r);
  }
  for (auto&& r : B) {
    scan(r);
  }
  for (auto&& [i, j] : std::views::cartesian_product(std::views::iota(0, n), std::views::iota(0, n))) {
    if (A[i][j] != B[i][j]) {
      println(i + 1, j + 1);
      return;
    }
  }
  assert(false);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}