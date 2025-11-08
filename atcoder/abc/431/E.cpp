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
  std::vector g(n, std::string(m, '#'));
  for (int i = 0; i < n; ++i) {
    Scan(g[i]);
  }

  std::array di = {
    std::array{+0, +1, -1, +0},
    std::array{+1, +0, +0, -1},
    std::array{-1, +0, +0, +1},
  };
  std::array dj = {
    std::array{+1, +0, +0, -1},
    std::array{+0, +1, -1, +0},
    std::array{+0, -1, +1, +0},
  };
  std::array dt = {
    std::array{0, 1, 2, 3},
    std::array{1, 0, 3, 2},
    std::array{2, 3, 0, 1},
  };

  // <cost, type, i, j,>
  using T = std::tuple<int, int, int, int>;
  auto pq = std::priority_queue(std::greater<T>{}, std::vector<T>{});
  std::vector dp(n, std::vector(m, std::vector(4, n * m + 1)));
  pq.emplace(dp[0][0][0] = 0, 0, 0, 0);

  while (!pq.empty()) {
    const auto [d, t, i, j] = pq.top();
    pq.pop();
    if (d != dp[i][j][t]) {
      continue;
    }
    for (char c : std::string("ABC")) {
      const auto ni = i + di[c - 'A'][t];
      const auto nj = j + dj[c - 'A'][t];
      const auto nt = dt[c - 'A'][t];
      if (std::clamp(ni, 0, n - 1) == ni && std::clamp(nj, 0, m - 1) == nj) {
        const auto nd = d + (c != g[i][j]);
        if (dp[ni][nj][nt] > nd) {
          pq.emplace(dp[ni][nj][nt] = nd, nt, ni, nj);
        }
      }
    }
  }
  auto ret = n * m + 1;
  for (int t = 0; t < 4; ++t) {
    for (char c : std::string("ABC")) {
      const auto ni = n - 1 + di[c - 'A'][t];
      const auto nj = m - 1 + dj[c - 'A'][t];
      const auto nt = dt[c - 'A'][t];
      if (ni == n - 1 && nj == m && nt == 0) {
        ret = std::min(ret, dp[n - 1][m - 1][t] + (g[n - 1][m - 1] != c));
      }
    }
  }
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  Scan(t);
  while (t-- > 0) {
    Solve();
  }
}
