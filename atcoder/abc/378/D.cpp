#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&& ... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

void solve() {
  int n, m, k;
  scan(n, m, k);
  std::vector<std::string> g(n);
  for (int i = 0; i < n; ++i) {
    scan(g[i]);
  }
  std::array dd{1, 0, -1, 0, 1};
  auto Dfs = [&](auto&& self, int i, int j, int x) -> int {
    if (x == k) {
      return 1;
    }
    int tot = 0;
    for (int s = 0; s < 4; ++s) {
      const auto ni = i + dd[s];
      const auto nj = j + dd[s + 1];
      if (std::clamp(ni, 0, n - 1) == ni && std::clamp(nj, 0, m - 1) == nj && g[ni][nj] == '.') {
        g[ni][nj] = '#';
        tot += self(self, ni, nj, x + 1);
        g[ni][nj] = '.';
      }
    }
    return tot;
  };
  int tot = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (g[i][j] == '.') {
        g[i][j] = '#';
        tot += Dfs(Dfs, i, j, 0);
        g[i][j] = '.';
      }
    }
  }
  println(tot);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}