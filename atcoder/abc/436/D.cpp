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
  std::vector g(n, std::string{});
  for (int i = 0; i < n; ++i) {
    Scan(g[i]);
  }

  auto ok = [n, m](const int i, const int j) {
    return std::clamp(i, 0, n - 1) == i && std::clamp(j, 0, m - 1) == j;
  };
  auto isW = [&g](const int i, const int j) {
    return std::clamp(g[i][j], 'a', 'z') == g[i][j];
  };

  using T = std::tuple<int, int, int>;
  constexpr auto kInf = std::numeric_limits<int>::max() / 2;
  constexpr int kA = 26;

  std::array<std::vector<std::pair<int, int>>, kA> byA;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (isW(i, j)) {
        byA[g[i][j] - 'a'].emplace_back(i, j);
      }
    }
  }

  std::vector dist(n, std::vector(m, kInf));
  auto pq = std::priority_queue(std::greater<T>{}, std::vector<T>{});
  pq.emplace(dist[0][0] = 0, 0, 0);
  while (!pq.empty()) {
    const auto [d, i, j] = pq.top();
    pq.pop();
    if (d != dist[i][j]) {
      continue;
    }
    for (auto di = -1; di < 2; ++di) {
      for (auto dj = -1; dj < 2; ++dj) {
        if (di * di + dj * dj != 1) {
          continue;
        }
        const auto ni = i + di;
        const auto nj = j + dj;
        if (ok(ni, nj) && g[ni][nj] != '#' && d + 1 < dist[ni][nj]) {
          pq.emplace(dist[ni][nj] = d + 1, ni, nj);
        }
      }
    }
    if (isW(i, j) && !byA[g[i][j] - 'a'].empty()) {
      for (const auto [ni, nj] : byA[g[i][j] - 'a']) {
        assert(g[i][j] == g[ni][nj]);
        if (d + 1 < dist[ni][nj]) {
          pq.emplace(dist[ni][nj] = d + 1, ni, nj);
        }
      }
      byA[g[i][j] - 'a'].clear();
    }
  }
  Println(dist[n - 1][m - 1] == kInf ? -1 : dist[n - 1][m - 1]);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
