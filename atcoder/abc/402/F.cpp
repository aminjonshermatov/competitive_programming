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
  std::vector g(n, std::vector(n, 0));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      Scan(g[i][j]);
    }
  }

  auto norm = [m](int64_t x) {
    return (x % m + m) % m;
  };

  if (n == 1) {
    Println(norm(g[0][0]));
    return;
  }

  auto ok = [n](const int i, const int j) {
    return std::clamp(i, 0, n - 1) == i && std::clamp(j, 0, n - 1) == j;
  };

  std::vector forw(n, std::vector(n, std::vector<int>{}));
  forw[0][0].emplace_back(norm(g[0][0]));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; i + j + 1 <= n && j < n; ++j) {
      for (auto [di, dj] : {std::pair(-1, 0), {0, -1}}) {
        const auto pi = i + di;
        const auto pj = j + dj;
        if (!ok(pi, pj)) {
          continue;
        }
        for (auto x : forw[pi][pj]) {
          forw[i][j].emplace_back(norm(x * 1LL * 10 + g[i][j]));
        }
      }
      std::ranges::sort(forw[i][j]);
      forw[i][j].erase(std::ranges::unique(forw[i][j]).begin(), forw[i][j].end());
    }
  }

  std::vector pw10(2 * n, 1);
  for (int i = 1; i <= 2 * n - 1; ++i) {
    pw10[i] = norm(pw10[i - 1] * 1LL * 10);
  }

  std::vector bacw(n, std::vector(n, std::vector<int>{}));
  bacw[n - 1][n - 1].emplace_back(norm(g[n - 1][n - 1]));
  for (int i = n - 1; i >= 0; --i) {
    for (int j = n - 1; (n - i - 1) + (n - j - 1) + 1 < n && j >= 0; --j) {
      for (auto [di, dj] : {std::pair(+1, 0), {0, +1}}) {
        const auto pi = i + di;
        const auto pj = j + dj;
        if (!ok(pi, pj)) {
          continue;
        }
        for (auto x : bacw[pi][pj]) {
          bacw[i][j].emplace_back(norm(g[i][j] * 1LL * pw10[n - i - 1 + n - j - 1] + x));
        }
      }
      std::ranges::sort(bacw[i][j]);
      bacw[i][j].erase(std::ranges::unique(bacw[i][j]).begin(), bacw[i][j].end());
    }
  }

  auto ret = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; i + j + 1 <= n && j < n; ++j) {
      for (auto x : forw[i][j]) {
        assert(2 * n - 1 - (i + j + 1) >= 0);
        const int me = norm(x * 1LL * pw10[2 * n - 1 - (i + j + 1)]);
        for (auto [di, dj] : {std::pair(+1, 0), {0, +1}}) {
          const auto ni = i + di;
          const auto nj = j + dj;
          if (!ok(ni, nj)) {
            continue;
          }
          const auto it = std::ranges::lower_bound(bacw[ni][nj], m - me);
          // me + a < m -> a < m-me
          if (it != bacw[ni][nj].begin()) {
            assert(me + *std::prev(it) < m);
            ret = std::max(ret, me + *std::prev(it));
          }
          // me + a >= m ==> me+a-m >= 0 -> a >= me-a
          if (it != bacw[ni][nj].end()) {
            assert(me + *it >= m);
            ret = std::max(ret, me + *it - m);
          }
        }
      }
    }
  }
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
