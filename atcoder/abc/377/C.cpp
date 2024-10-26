#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&& ... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

std::array di{-2, -2, -1, -1, +1, +1, +2, +2};
std::array dj{-1, +1, -2, +2, -2, +2, -1, +1};

void solve() {
  int n, m;
  scan(n, m);
  std::set<std::pair<int, int>> uniq;
  for (int _ = 0; _ < m; ++_) {
    int i, j;
    scan(i, j);
    uniq.emplace(i, j);
    for (int k = 0; k < 8; ++k) {
      const auto ni = i + di[k];
      const auto nj = j + dj[k];
      if (std::clamp(ni, 1, n) == ni && std::clamp(nj, 1, n) == nj) {
        uniq.emplace(ni, nj);
      }
    }
  }
  dbg(uniq);
  println(n * 1LL * n - uniq.size());
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}