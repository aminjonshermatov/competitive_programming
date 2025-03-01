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
  int64_t x;
  Scan(n, m, x);
  std::vector<std::vector<std::pair<int, bool>>> g(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    Scan(u, v);
    --u, --v;
    g[u].emplace_back(v, false);
    g[v].emplace_back(u, true);
  }
  constexpr auto kInf = std::numeric_limits<int64_t>::max() / 3;

  std::vector dist(n, std::vector(2, kInf));
  using T = std::tuple<int64_t, int, bool>;
  std::priority_queue<T, std::vector<T>, std::greater<>> pq;
  pq.emplace(dist[0][0] = 0, 0, false);
  pq.emplace(dist[0][1] = x, 0, true);
  while (!pq.empty()) {
    const auto [d, v, reversed] = pq.top();
    pq.pop();
    if (dist[v][reversed] != d) {
      continue;
    }
    for (const auto [u, isReversed] : g[v]) {
      const auto newD = d + 1 + (reversed == isReversed ? 0 : x);
      if (newD < dist[u][isReversed]) {
        pq.emplace(dist[u][isReversed] = newD, u, isReversed);
      }
    }
  }

  Println(std::ranges::min(dist[n - 1]));
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
