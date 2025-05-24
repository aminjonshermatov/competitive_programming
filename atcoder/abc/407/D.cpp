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
  std::vector g(n, std::vector(m, int64_t{}));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      Scan(g[i][j]);
    }
  }

  auto id = [m](const int i, const int j) {
    return i * m + j;
  };
  auto ok = [n, m](const int i, const int j) {
    return std::clamp(i, 0, n - 1) == i && std::clamp(j, 0, m - 1) == j;
  };

  const auto tot = n * m;
  constexpr auto kInf = std::numeric_limits<int64_t>::max() / 2;
  std::vector dp(1 << tot, -kInf);
  dp[0] = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      dp[0] ^= g[i][j];
    }
  }

  constexpr std::array kDi{-1, +0, +0, +1};
  constexpr std::array kDj{+0, -1, +1, +0};
  for (int msk = 0; msk < (1 << tot); ++msk) {
    for (auto tmp = ~msk & ((1 << tot) - 1); tmp > 0;) {
      const auto b = std::__lg(tmp);
      const auto [i, j] = std::div(b, m);
      for (int k = 0; k < 4; ++k) {
        const auto ni = i + kDi[k];
        const auto nj = j + kDj[k];
        if (!ok(ni, nj) || (msk >> id(ni, nj) & 1) == 1) {
          continue;
        }
        const auto nMsk = msk | (1 << id(i, j)) | (1 << id(ni, nj));
        dp[nMsk] = std::max(dp[nMsk], dp[msk] ^ g[i][j] ^ g[ni][nj]);
      }
      tmp ^= 1 << b;
    }
  }
  Println(std::ranges::max(dp));
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
