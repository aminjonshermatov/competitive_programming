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
    --as[i];
  }

  auto imin = [](auto& a, const auto& b) {
    return a > b && (a = b, true);
  };
  auto imax = [](auto& a, const auto& b) {
    return a < b && (a = b, true);
  };

  const auto maxA = std::ranges::max(as) + 1;
  std::vector<std::vector<int>> ids(maxA);
  for (int i = 0; i < n; ++i) {
    ids[as[i]].emplace_back(i);
  }

  std::vector<int> dp(1 << maxA, n);
  const auto full = (1U << maxA) - 1;
  dp[0] = -1;
  for (uint32_t m = 0U; m < (1 << maxA); ++m) {
    for (auto tmp = ~m & full; tmp > 0;) {
      const auto b = std::bit_width(tmp) - 1;
      const auto last = dp[m];
      auto pos = std::distance(ids[b].begin(), std::ranges::upper_bound(ids[b], last));
      if (pos + 1 < ids[b].size()) {
        imin(dp[m | (1U << b)], ids[b][pos + 1]);
      }
      tmp ^= 1U << b;
    }
  }
  uint32_t ret = 0U;
  for (uint32_t m = 0U; m < (1 << maxA); ++m) {
    if (dp[m] < n) {
      imax(ret, std::popcount(m));
    }
  }
  Println(ret * 2);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
