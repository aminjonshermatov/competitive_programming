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
  int n;
  Scan(n);
  std::vector<int> as(n);
  for (int i = 0; i < n; ++i) {
    Scan(as[i]);
  }

  std::ranges::sort(as);
  as.erase(std::ranges::unique(as).begin(), as.end());
  Println(as.size());
  for (auto a : as) {
    Print(a);
  }
  Println();
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
