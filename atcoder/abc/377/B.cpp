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
  std::array<std::string, 8> g{};
  std::set<int> row, col;
  for (int i = 0; i < 8; ++i) {
    scan(g[i]);
    for (int j = 0; j < 8; ++j) {
      if (g[i][j] == '#') {
        row.emplace(i);
        col.emplace(j);
      }
    }
  }
  for (auto i : row) {
    for (int j = 0; j < 8; ++j) {
      g[i][j] = '#';
    }
  }
  for (auto j : col) {
    for (int i = 0; i < 8; ++i) {
      g[i][j] = '#';
    }
  }
  int tot = 0;
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      tot += g[i][j] == '.';
    }
  }
  println(tot);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}