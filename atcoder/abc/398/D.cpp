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
  int n, r, c;
  std::string s;
  Scan(n, r, c, s);

  auto go = [&](const char c) -> std::pair<int, int> {
    if (c == 'N') {
      return {-1, 0};
    } else if (c == 'W') {
      return {0, -1};
    } else if (c == 'S') {
      return {+1, 0};
    } else if (c == 'E') {
      return {0, +1};
    }
    std::unreachable();
  };

  auto curR = 0, curC = 0;
  std::set<std::pair<int, int>> hist;
  hist.emplace(0, 0);
  for (int i = 0; i < n; ++i) {
    auto [dr, dc] = go(s[i]);
    curR += dr, curC += dc;
    std::cout << hist.contains(std::pair(curR - r, curC - c));
    if (!hist.contains(std::pair(curR, curC))) {
      hist.emplace(curR, curC);
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
