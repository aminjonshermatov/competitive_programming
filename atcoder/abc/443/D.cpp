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
  auto tot = 0LL;
  for (int i = 0; i < n; ++i) {
    Scan(as[i]);
    tot += as[i];
  }

  for (int i = 1; i < n; ++i) {
    as[i] = std::min(as[i], as[i - 1] + 1);
  }
  for (int i = n - 2; i >= 0; --i) {
    as[i] = std::min(as[i], as[i + 1] + 1);
  }
  Println(tot - std::ranges::fold_left(as, 0LL, std::plus{}));
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  Scan(t);
  while (t-- > 0) {
    Solve();
  }
}
