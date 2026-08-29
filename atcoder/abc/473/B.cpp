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
  std::map<int, int> xs;
  for (int i = 0; i < n; ++i) {
    int x;
    Scan(x);
    ++xs[x];
  }
  auto s = 0;
  for (const auto [k, v] : xs) {
    if (v % 2 == 1) {
      s += k;
    }
  }
  Println(s);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
