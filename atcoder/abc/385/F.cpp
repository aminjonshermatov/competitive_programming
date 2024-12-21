#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

using Ld = __float128;

void Solve() {
  int n;
  Scan(n);
  std::vector<int64_t> xs(n), hs(n);
  for (int i = 0; i < n; ++i) {
    Scan(xs[i], hs[i]);
  }
  auto can = [&](const Ld h) -> bool {
    auto prv = static_cast<Ld>(std::numeric_limits<int64_t>::min());
    for (int i = 0; i < n; ++i) {
      const auto cur = static_cast<Ld>(hs[i] - h) / xs[i];
      if (prv >= cur) {
        return true;
      }
      prv = cur;
    }
    return false;
  };
  Ld lo = .0, hi = 1LL << 61;
  if (!can(lo)) {
    Println(-1);
    return;
  }
  for (int _ = 0; _ < 120; ++_) {
    const auto mid = (lo + hi) * .5;
    (can(mid) ? lo : hi) = mid;
  }
  std::cout << std::fixed << std::setprecision(15) << static_cast<long double>(lo) << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
