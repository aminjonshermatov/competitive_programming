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
  std::vector<int> as(2 * n);
  for (auto&& a : as) {
    scan(a);
  }

  int tot{};
  for (int i = 1; i <= n; ++i) {
    int cnt{};
    for (int j = 1; j + 1 < 2 * n; ++j) {
      cnt += as[j - 1] == i && as[j + 1] == i;
    }
    tot += cnt == 1;
  }
  println(tot);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}