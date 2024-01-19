#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using i64 = int64_t;

void solve() {
  int n;
  std::cin >> n;
  std::vector as(n, std::vector<i64>(n));
  for (auto& r : as) {
    for (auto& x : r) {
      std::cin >> x;
    }
  }

  std::vector<i64> sum(1 << n, 0);
  for (int m = 0; m < (1 << n); ++m) {
    for (int i = 0; i < n; ++i) {
      if (m >> i & 1) {
        for (int j = i + 1; j < n; ++j) {
          if (m >> j & 1) {
            sum[m] += as[i][j];
          }
        }
      }
    }
  }

  std::vector<i64> dp(1 << n, 0);
  for (int m = 0; m < (1 << n); ++m) {
    for (int s = m; s > 0; s = (s - 1) & m) {
      dp[m] = std::max(dp[m], dp[m ^ s] + sum[s]);
    }
  }
  std::cout << dp[(1 << n) - 1] << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
