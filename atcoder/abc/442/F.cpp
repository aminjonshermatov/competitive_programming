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
  std::vector<std::string> g(n);
  for (int i = 0; i < n; ++i) {
    Scan(g[i]);
  }
  
  std::vector dp(n, 0), ndp(n, 0), pf(n, 0), sfMin(n, 0);
  auto bot = 0;
  for (int i = 0; i < n; ++i) {
    bot += std::ranges::count(g[i], '.');
  }
  
  auto qry = [&](const int l, const int r) -> int {
    if (!(0 <= l && l <= r && r < n)) {
      return 0;
    }
    return pf[r] - (l > 0 ? pf[l - 1] : 0);
  };

  auto ret = bot;
  for (int i = 0; i < n; ++i) {
    std::ranges::fill(pf, 0);
    for (int j = 0; j < n; ++j) {
      pf[j] = (j > 0 ? pf[j - 1] : 0) + (g[i][j] == '#');
    }
    sfMin[n - 1] = dp[n - 1];
    for (int j = n - 2; j >= 0; --j) {
      sfMin[j] = std::min(sfMin[j + 1], dp[j]);
    }
    for (int j = 0; j < n; ++j) {
      ndp[j] = qry(0, j) + (n - j - 1 - qry(j + 1, n - 1)) + sfMin[j];
    }
    bot -= std::ranges::count(g[i], '.');
    ret = std::min(ret, std::ranges::min(ndp) + bot);
    std::swap(dp, ndp);
  }
  Println(std::min(ret, std::ranges::min(dp)));
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
