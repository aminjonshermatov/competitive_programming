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

  auto tot = 0;
  for (int i = 0; i < n; ++i) {
    auto s = 0;
    for (int j = i; j < n; ++j) {
      s += as[j];
      auto f = true;
      for (int k = i; k <= j; ++k) {
        f &= s % as[k] != 0;
      }
      tot += f;
    }
  }
  Println(tot);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
