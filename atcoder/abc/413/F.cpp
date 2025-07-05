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
  int n, m, k;
  Scan(n, m, k);

  using T = std::tuple<int, int, int>;
  auto pq = std::priority_queue(std::greater<T>{}, std::vector<T>{});
  constexpr auto kInf = std::numeric_limits<int>::max() / 2;
  std::vector dist(n, std::vector(m, kInf));
  for (int i = 0; i < k; ++i) {
    int x, y;
    Scan(x, y);
    --x, --y;
    pq.emplace(dist[x][y] = 0, x, y);
  }

  constexpr std::array kDk{1, 0, -1, 0, 1};
  auto ok = [n, m](const int i, const int j) {
    return std::clamp(i, 0, n - 1) == i && std::clamp(j, 0, m - 1) == j;
  };
  while (!pq.empty()) {
    const auto [d, i, j] = pq.top();
    pq.pop();
    if (d != dist[i][j]) {
      continue;
    }
    for (int x = 0; x < 4; ++x) {
      const auto ni = i + kDk[x];
      const auto nj = j + kDk[x + 1];
      if (!ok(ni, nj)) {
        continue;
      }
      if (dist[ni][nj] == kInf) {
        ++dist[ni][nj];
      } else if (dist[ni][nj] > kInf) {
        pq.emplace(dist[ni][nj] = d + 1, ni, nj);
      }
    }
  }

  auto tot = int64_t{};
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (dist[i][j] >= kInf) {
        dist[i][j] = 0;
      }
      tot += dist[i][j];
    }
  }
  Println(tot);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
