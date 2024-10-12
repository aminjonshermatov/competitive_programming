#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&& ... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

using i64 = int64_t;

constexpr bool imin(auto&& a, auto&& b) noexcept {
  return a > b && (a = b, true);
}

void solve() {
  int n, m, q;
  scan(n, m, q);
  std::vector<i64> as(m), bs(m), cs(m);
  for (int i = 0; i < m; ++i) {
    scan(as[i], bs[i], cs[i]);
    --as[i], --bs[i];
  }
  std::vector<std::tuple<char, int, int>> qs(q);
  std::vector<bool> av(m, true);
  for (auto& [cmd, x, y] : qs) {
    scan(cmd, x);
    --x;
    if (cmd == '1') {
      av[x] = false;
    } else {
      scan(y);
      --y;
    }
  }
  constexpr auto inf = std::numeric_limits<i64>::max() / 3;
  std::vector dist(n, std::vector(n, inf));
  for (int i = 0; i < n; ++i) {
    dist[i][i] = 0;
  }
  for (int i = 0; i < m; ++i) {
    if (av[i]) {
      imin(dist[as[i]][bs[i]], cs[i]);
      imin(dist[bs[i]][as[i]], cs[i]);
    }
  }

  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        imin(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }

  std::vector<i64> ret;
  ret.reserve(q);
  for (int i = q - 1; i >= 0; --i) {
    const auto [cmd, x, y] = qs[i];
    if (cmd == '1') {
      assert(!av[x]);
      imin(dist[as[x]][bs[x]], cs[x]);
      imin(dist[bs[x]][as[x]], cs[x]);
      for (int a = 0; a < n; ++a) {
        for (int b = 0; b < n; ++b) {
          imin(dist[a][b], dist[a][as[x]] + dist[as[x]][b]);
          imin(dist[a][b], dist[a][bs[x]] + dist[bs[x]][b]);
        }
      }
      for (int a = 0; a < n; ++a) {
        for (int b = 0; b < n; ++b) {
          imin(dist[a][b], dist[a][bs[x]] + dist[bs[x]][b]);
          imin(dist[a][b], dist[a][as[x]] + dist[as[x]][b]);
        }
      }
    } else {
      ret.emplace_back(dist[x][y] == inf ? -1 : dist[x][y]);
    }
  }
  for (auto x : ret | std::views::reverse) {
    print(x);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}