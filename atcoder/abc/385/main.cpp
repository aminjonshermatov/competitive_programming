#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

using Ld = long double;
constexpr Ld kEps = 1e-12;

void Solve() {
  int n;
  Scan(n);
  std::vector<int> xs(n), hs(n);
  for (int i = 0; i < n; ++i) {
    Scan(xs[i], hs[i]);
  }
  auto can = [&](const Ld h) -> bool {
    // add(x, y) -> add point
    // qry(k, b) -> query if there are exists (x', y'): y' >= k*x' + b
    return false;
  };
  Ld lo = .0, hi = std::ranges::max(hs) + 1;
  if (!can(lo)) {
    Println(-1);
    return;
  }
  for (int _ = 0; _ < 120; ++_) {
    const auto mid = lo + (hi - lo) / 2;
    (can(mid) ? lo : hi) = mid;
  }
  std::cout << std::fixed << std::setprecision(15) << lo << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
