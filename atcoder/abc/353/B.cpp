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
  int n, k;
  scan(n, k);
  int cnt = 0, cur = 0;
  for (int i = 0; i < n; ++i) {
    int x;
    scan(x);
    if (cur + x <= k) {
      cur += x;
    } else {
      cur = x;
      ++cnt;
    }
  }
  println(cnt + 1);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}