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
  int n, k;
  Scan(n, k);
  std::vector<int> as(n + 1);
  for (int i = 1; i <= n; ++i) {
    Scan(as[i]);
  }

  std::map<int, std::vector<int>> ids;
  std::vector pf(n + 1, 0LL);
  for (int i = 1; i <= n; ++i) {
    pf[i] = (pf[i - 1] + as[i]) % k;
    if (pf[i] < 0) {
      pf[i] += k;
    }
    ids[pf[i]].emplace_back(i);
  }
  std::vector dp(n + 1, 0);
  std::map<int64_t, int> best;
  best[0] = 0;
  for (int i = 1; i <= n; ++i) {
    dp[i] = dp[i - 1];
    if (const auto it = best.find(pf[i]); it != best.end()) {
      dp[i] = std::max(dp[i], it->second + 1);
    }
    best[pf[i]] = std::max(best[pf[i]], dp[i]);
    // dp[i] = dp[i - 1];
    // for (int j = 1; j <= i; ++j) {
    //   if (pf[i] == pf[j - 1]) {
    //     dp[i] = std::max(dp[i], dp[j - 1] + 1);
    //   }
    // }
  }
  Println(std::ranges::max(dp));
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
