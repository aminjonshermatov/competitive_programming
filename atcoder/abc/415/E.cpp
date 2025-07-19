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
  std::vector g(n, std::vector(m, 0));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      Scan(g[i][j]);
    }
  }
  std::vector cs(n + m - 1, 0);
  for (int i = 0; i < n + m - 1; ++i) {
    Scan(cs[i]);
  }

  auto can = [&](const int64_t s) -> bool {
    constexpr auto kInf = std::numeric_limits<int64_t>::max() / 2;
    std::vector dp(n, std::vector(m, -kInf));
    if (g[0][0] + s < cs[0]) {
      return false;
    }
    dp[0][0] = g[0][0] + s - cs[0];
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (i > 0 && dp[i - 1][j] + g[i][j] >= cs[i + j]) {
          dp[i][j] = std::max(dp[i][j], dp[i - 1][j] + g[i][j] - cs[i + j]);
        }
        if (j > 0 && dp[i][j - 1] + g[i][j] >= cs[i + j]) {
          dp[i][j] = std::max(dp[i][j], dp[i][j - 1] + g[i][j] - cs[i + j]);
        }
      }
    }
    return dp[n - 1][m - 1] != -kInf;
  };

  int64_t lo = -1, hi = 1E15;
  while (hi - lo > 1) {
    const auto mid = std::midpoint(lo, hi);
    (can(mid) ? hi : lo) = mid;
  }
  Println(hi);
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
