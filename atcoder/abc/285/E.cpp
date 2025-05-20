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
  std::vector<int64_t> as(n);
  for (int i = 0; i < n; ++i) {
    Scan(as[i]);
  }

  std::vector<int64_t> pf(n + 1, 0);
  for (int i = 1; i <= n; ++i) {
    pf[i] = pf[i - 1] + as[(i + 1) / 2 - 1];
  }

  constexpr auto kInf = std::numeric_limits<int64_t>::max() / 2;
  std::vector dp(n, std::vector(n, -kInf));
  dp[0][0] = 0;
  for (int i = 1; i < n; ++i) {
    for (int j = 1; j < n; ++j) {
      dp[i][j] = std::max(dp[i][j], dp[i - 1][j - 1]);
      dp[i][0] = std::max(dp[i][0], dp[i - 1][j] + pf[j]);
    }
  }
  auto ret = -kInf;
  for (int j = 0; j < n; ++j) {
    ret = std::max(ret, dp[n - 1][j] + pf[j]);
  }
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
