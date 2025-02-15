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
  int n, m;
  Scan(n, m);

  std::set<std::pair<int, int>> es;
  auto ret = 0;
  for (int i = 0; i < m; ++i) {
    int u, v;
    Scan(u, v);
    if (u > v) {
      std::swap(u, v);
    }
    if (u == v || es.contains(std::pair(u, v))) {
      ++ret;
    }
    es.emplace(u, v);
  }
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
