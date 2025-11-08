#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

constexpr auto IMax(auto& a, const auto& b) noexcept {
  return a < b && (a = b, true);
}

void Solve() {
  int n;
  Scan(n);
  std::vector<int64_t> ws(n), hs(n), bs(n);
  for (int i = 0; i < n; ++i) {
    Scan(ws[i], hs[i], bs[i]);
  }

  const auto tot = std::ranges::fold_left(ws, 0, std::plus{});
  std::vector<int64_t> dp(2 * tot + 1, -1E18), ndp(2 * tot + 1);
  dp[tot] = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= 2 * tot; ++j) {
      ndp[j] = dp[j];
    }
    for (int j = 0; j <= 2 * tot; ++j) {
      if (j >= ws[i]) {
        IMax(ndp[j - ws[i]], dp[j] + hs[i]);
      }
      if (j + ws[i] <= 2 * tot) {
        IMax(ndp[j + ws[i]], dp[j] + bs[i]);
      }
    }
    for (int j = 0; j <= 2 * tot; ++j) {
      dp[j] = ndp[j];
    }
  }
  auto ret = 0LL;
  for (int i = tot; i <= 2 * tot; ++i) {
    IMax(ret, dp[i]);
  }
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
