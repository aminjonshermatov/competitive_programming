#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  using i64 = int64_t;
  int n, m;
  std::cin >> n >> m;
  std::vector g(n + 1, std::vector<i64>(n + 1));
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      std::cin >> g[i][j];
    }
  }

  std::vector pf(n + 1, std::vector<i64>(n + 1, 0));
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      pf[i][j] = pf[i - 1][j] + pf[i][j - 1] - pf[i - 1][j - 1] + g[i][j];
    }
  }
  auto qry = [&](int i, int j) -> i64 {
    return pf[i + m - 1][j + m - 1] - pf[i - 1][j + m - 1] - pf[i + m - 1][j - 1] + pf[i - 1][j - 1];
  };

  auto splitByRows = [&]() -> i64 {
    return 0;
  };
  auto splitByCols = [&]() -> i64 {
    return 0;
  };
  auto splitByBoth = [&]() -> i64 {
    return 0;
  };

  std::cout << std::max({splitByRows(), splitByCols(), splitByBoth()}) << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}