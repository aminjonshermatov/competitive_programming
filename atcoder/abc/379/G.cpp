#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&& ... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

constexpr int mod = 998244353;

constexpr int add(int a, int b) noexcept {
  if ((a += b) >= mod) {
    a -= mod;
  }
  return a;
}

void solve() {
  int n, m;
  scan(n, m);
  std::vector<std::string> g(n);
  for (int i = 0; i < n; ++i) {
    scan(g[i]);
  }
  if (n < m) {
    std::vector ng(m, std::string(n, '#'));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        ng[j][i] = g[i][j];
      }
    }
    std::swap(g, ng);
    std::swap(n, m);
  }

  using i64 = int64_t;
  i64 b = 1LL << (2 * m - 2);
  std::map<i64, int> dp;
  dp[0] = 1;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::map<i64, int> ndp;
      for (auto [k, v] : dp) {
        for (int x = 1; x <= 3; ++x) {
          if (g[i][j] != '?' && g[i][j] - '1' != x - 1) {
            continue;
          }
          const auto q = k >> (2 * m - 2);
          const auto r = k & (b - 1);
          if ((j > 0 && (k & 3) == x) || q == x) {
            continue;
          }
          const auto nk = ((r << 2) + x);
          assert(nk < (b << 2));
          ndp[nk] = add(ndp[nk], v);
        }
      }
      std::swap(dp, ndp);
    }
  }
  int tot = 0;
  for (auto v : dp | std::ranges::views::values) {
    tot = add(tot, v);
  }
  println(tot);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}