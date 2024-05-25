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
  int n, t;
  scan(n, t);

  std::map<int, int> row, col, diag1, diag2;
  int ret = -1;
  for (int i = 0; i < t; ++i) {
    int x;
    scan(x);
    --x;
    auto [r, c] = std::div(x, n);
    if ((++row[r] == n || ++col[c] == n || ++diag1[r - c] == n || ++diag2[r + c] == n) && ret == -1) {
      ret = i + 1;
    }
  }
  println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}