#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

void Solve() {
  int n, m, d;
  Scan(n, m, d);
  std::vector<std::string> g(n);
  for (int i = 0; i < n; ++i) {
    Scan(g[i]);
  }
  int best = 0;
  std::vector<std::pair<int, int>> may;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (g[i][j] == '.') {
        may.emplace_back(i, j);
      }
    }
  }
  auto dist = [&](std::size_t i, std::size_t j) {
    return std::abs(may[i].first - may[j].first) + std::abs(may[i].second - may[j].second);
  };
  for (std::size_t x{0}; x < may.size(); ++x) {
    for (std::size_t y{x + 1}; y < may.size(); ++y) {
      int loc = 0;
      for (std::size_t z{0}; z < may.size(); ++z) {
        loc += z == x || z == y || dist(z, x) <= d || dist(z, y) <= d;
      }
      best = std::max(best, loc);
    }
  }
  Println(best);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
