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

  auto ok = [n](const int i, const int j) {
    return std::clamp(i, 0, n - 1) == i && std::clamp(j, 0, n - 1) == j;
  };

  constexpr std::array kDi{-2, -2, -1, -1, +1, +1, +2, +2};
  constexpr std::array kDj{-1, +1, -2, +2, -2, +2, -1, +1};

  constexpr auto kInf = std::numeric_limits<int>::max() / 2;
  std::vector dist(n, std::vector(n, kInf));
  using T = std::tuple<int, int, int>;
  auto pq = std::priority_queue(std::greater<T>{}, std::vector<T>{});
  pq.emplace(dist[0][0] = 0, 0, 0);
  while (!pq.empty()) {
    const auto [d, i, j] = pq.top();
    pq.pop();
    if (d != dist[i][j]) {
      continue;
    }
    for (int k = 0; k < 8; ++k) {
      const auto ni = i + kDi[k];
      const auto nj = j + kDj[k];
      if (ok(ni, nj) && dist[ni][nj] > d + 1) {
        pq.emplace(dist[ni][nj] = d + 1, ni, nj);
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      Print(dist[i][j]);
    }
    Println();
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
