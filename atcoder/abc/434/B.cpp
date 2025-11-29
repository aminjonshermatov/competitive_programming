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
  std::vector sum(m, 0), qty(m, 0);
  for (int i = 0; i < n; ++i) {
    int a, b;
    Scan(a, b);
    --a;
    sum[a] += b;
    ++qty[a];
  }

  for (int k = 0; k < m; ++k) {
    std::cout << std::fixed << std::setprecision(15) << static_cast<long double>(sum[k]) / qty[k] << '\n';
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
