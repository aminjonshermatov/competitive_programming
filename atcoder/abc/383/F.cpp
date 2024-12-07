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
  int n, x, k;
  Scan(n, x, k);
  std::vector<std::vector<std::pair<int, int64_t>>> byCol(n);
  for (int i = 0; i < n; ++i) {
    int p, c;
    int64_t u;
    Scan(p, u, c);
    --c;
    byCol[c].emplace_back(p, u);
  }

  // dp(price)
  constexpr auto kInf = std::numeric_limits<int64_t>::max() / 3;
  std::vector dp(x + 1, -kInf);
  dp[0] = 0;
  for (int col = 0; col < n; ++col) {
    std::vector ndp(x + 1, -kInf);
    for (const auto [p, u] : byCol[col]) {
      for (auto curX = x - p; curX >= 0; --curX) {
        ndp[curX + p] = std::max<int64_t>(ndp[curX + p], dp[curX] + u + k);
        ndp[curX + p] = std::max<int64_t>(ndp[curX + p], ndp[curX] + u);
      }
    }
    for (int curX = 0; curX <= x; ++curX) {
      ndp[curX] = std::max(ndp[curX], dp[curX]);
    }
    std::swap(dp, ndp);
  }
  Println(std::ranges::max(dp));
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
