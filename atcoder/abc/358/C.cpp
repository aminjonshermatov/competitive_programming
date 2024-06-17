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
  std::vector<std::string> g(n);
  for (auto&& r : g) {
    scan(r);
  }
  int ret = n + 1;
  const auto all = (1 << m) - 1;
  for (int mask = 1; mask < (1 << n); ++mask) {
    int cur{};
    for (auto tmp = mask; tmp > 0;) {
      const auto i = std::__lg(tmp);
      for (int j = 0; j < m; ++j) {
        if (g[i][j] == 'o') {
          cur |= 1 << j;
        }
      }
      tmp ^= 1 << i;
    }
    if (cur == all) {
      ret = std::min(ret, __builtin_popcount(mask));
    }
  }
  println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}