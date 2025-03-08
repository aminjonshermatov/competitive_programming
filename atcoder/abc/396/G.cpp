#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

void Brute() {
  int n, m;
  Scan(n, m);
  std::vector g(n, uint32_t{0});
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      char f;
      Scan(f);
      g[i] = g[i] << 1 | (f - '0');
    }
  }

  constexpr auto kInf = std::numeric_limits<uint32_t>::max() / 2;
  std::vector dp(1 << m, uint32_t{0});
  for (int i = 0; i < n; ++i) {
    std::vector ndp(1 << m, kInf);
    for (int msk = 0; msk < (1 << m); ++msk) {
      const auto gi = std::popcount(g[i] ^ msk);
      ndp[msk] = std::min(ndp[msk], dp[msk] + std::min(gi, m - gi));
    }
    std::swap(dp, ndp);
  }
  Println(std::ranges::min(dp));
}

void Solve() {
  int n, m;
  Scan(n, m);

  // dp[c][x] = # i: popcount(g[i] ^ x) == c
  std::vector dp(m + 1, std::vector(1 << m, 0));
  for (int i = 0; i < n; ++i) {
    uint32_t val{0};
    for (int j = 0; j < m; ++j) {
      char f;
      Scan(f);
      val = val << 1 | (f - '0');
    }
    ++dp[0][val];
  }
  for (int b = 0; b < m; ++b) {
    for (int c = m - 1; c >= 0; --c) {
      for (int x = 0; x < (1 << m); ++x) {
        dp[c + 1][x] += dp[c][x ^ (1 << b)];
      }
    }
  }
  dbg(dp);
  auto ret = std::numeric_limits<int>::max();
  for (int x = 0; x < (1 << m); ++x) {
    auto loc = 0;
    for (int c = 0; c <= m; ++c) {
      loc += dp[c][x] * std::min(c, m - c);
    }
    ret = std::min(ret, loc);
  }
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
