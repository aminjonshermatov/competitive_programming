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
  int n, m;
  scan(n, m);
  std::vector<int> as(m);
  for (auto&& a : as) {
    scan(a);
  }
  std::vector<int> got(m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      int x;
      scan(x);
      got[j] += x;
    }
  }
  for (int i = 0; i < m; ++i) {
    if (got[i] < as[i]) {
      println("No");
      return;
    }
  }
  println("Yes");
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}