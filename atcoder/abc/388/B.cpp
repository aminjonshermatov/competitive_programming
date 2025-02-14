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
  int n, d;
  Scan(n, d);
  std::vector<int> ts(n), ls(n);
  for (int i = 0; i < n; ++i) {
    Scan(ts[i], ls[i]);
  }
  for (int k = 1; k <= d; ++k) {
    auto best = 0;
    for (int i = 0; i < n; ++i) {
      best = std::max(best, ts[i] * (ls[i] + k));
    }
    Print(best);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
