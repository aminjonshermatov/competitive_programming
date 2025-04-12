#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

auto Work() {
  int n;
  Scan(n);
  std::vector<std::vector<int>> g(n);
  for (int i = 0; i + 1 < n; ++i) {
    int u, v;
    Scan(u, v);
    --u, --v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }

  auto bfs = [&](const int from) {
    std::vector dist(n, -1);
    std::queue<int> que;
    que.emplace(from);
    dist[from] = 0;
    while (!que.empty()) {
      const auto u = que.front();
      que.pop();
      for (const auto v : g[u]) {
        if (dist[v] == -1) {
          dist[v] = dist[u] + 1;
          que.emplace(v);
        }
      }
    }
    return dist;
  };

  auto tmp = bfs(0);
  const auto fwd = bfs(std::ranges::max_element(tmp) - tmp.begin());
  const auto bwd = bfs(std::ranges::max_element(fwd) - fwd.begin());
  std::vector best(n, 0);
  for (int i = 0; i < n; ++i) {
    best[i] = std::max(fwd[i], bwd[i]);
  }
  return std::tuple(n, best);
}

void Solve() {
  auto [n1, maxPath1] = Work();
  auto [n2, maxPath2] = Work();

  std::ranges::sort(maxPath2);
  std::vector<int64_t> pf(n2);
  for (int i = 0; i < n2; ++i) {
    pf[i] = (i > 0 ? pf[i - 1] : 0) + maxPath2[i];
  }
  auto get = [&](int i, int j) {
    return pf[j] - (i > 0 ? pf[i - 1] : 0);
  };
  const auto diam = std::max(std::ranges::max(maxPath1), maxPath2.back());
  int64_t tot = 0;
  for (int i = 0; i < n1; ++i) {
    const int j = std::ranges::lower_bound(maxPath2, diam - maxPath1[i]) - maxPath2.begin();
    tot += j * 1LL * diam + (n2 - j) * 1LL * maxPath1[i] + get(j, n2 - 1) + n2 - j;
  }
  Println(tot);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
