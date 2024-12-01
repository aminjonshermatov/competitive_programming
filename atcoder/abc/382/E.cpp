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
  int n, x;
  Scan(n, x);
  using Ld = long double;
  std::vector<Ld> ps(n);
  for (int i = 0; i < n; ++i) {
    Scan(ps[i]);
    ps[i] /= 100;
  }
  dbg(ps);
  std::vector<Ld> dp(n + 1);
  dp[0] = 1;
  for (int i = 0; i < n; ++i) {
    std::vector<Ld> ndp(n + 1);
    for (int j = 0; j <= n; ++j) {
      ndp[j] += (1 - ps[i]) * dp[j];
      if (j > 0) {
        ndp[j] += ps[i] * dp[j - 1];
      }
    }
    std::swap(dp, ndp);
  }
  std::vector<Ld> es(x + 1);
  es[0] = 0;
  // E[x] = 1 + sum_{i=0}^{n} ( E[x - i] * dp[i] )
  for (int i = 1; i <= x; ++i) {
    for (int j = 1; j <= n; ++j) {
      es[i] += es[std::max(0, i - j)] * dp[j];
    }
    es[i] = (es[i] + 1) / (1 - dp[0]);
  }
  std::cout << std::fixed << std::setprecision(10) << es[x] << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
