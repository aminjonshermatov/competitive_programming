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
  int64_t n;
  int m;
  Scan(n, m);
  std::vector ex(301, 0);
  for (int i = 0; i < m; ++i) {
    int a, b;
    Scan(a, b);
    ex[a] = std::max(ex[a], b);
  }
  std::vector<std::pair<int, int>> es;
  for (int a = 0; a < 301; ++a) {
    if (ex[a] > 0) {
      es.emplace_back(a, ex[a]);
    }
  }

  constexpr int kN = 1E5;
  std::vector dp(kN, int64_t{0});
  for (int i = 0; i < kN; ++i) {
    dp[i] = i;
    for (auto [a, b] : es) {
      if (i >= a) {
        dp[i] = std::max(dp[i], dp[i - a + b] + a);
      }
    }
  }
  if (n < kN) {
    Println(dp[n]);
    return;
  }
  auto ret = int64_t{0};
  for (auto [a, b] : es) {
    const auto cnt = (n - kN) / (a - b) + 1;
    ret = std::max(ret, dp[n - cnt * (a - b)] + cnt * a);
  }
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
