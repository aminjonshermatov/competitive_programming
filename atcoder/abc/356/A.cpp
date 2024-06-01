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
  int n, l, r;
  scan(n, l, r);
  std::vector<int> as(n);
  std::iota(as.begin(), as.end(), 1);
  std::reverse(as.begin() + l - 1, as.begin() + r);
  for (const auto a : as) {
    print(a);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}