#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&&... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&&... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&&... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

void solve() {
  int n, m;
  scan(n, m);
  std::vector<std::vector<int>> g(n);
  for (auto&& _ : std::views::iota(0, m)) {
    int u, v;
    scan(u, v);
    --u, --v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }
  std::optional<int> grith;
  for (auto&& V : std::views::iota(0, n)) {
    std::vector<int> dist(n, -1);
    dist[V] = 0;
    std::queue<std::pair<int, int>> q;
    q.emplace(V, -1);
    while (!q.empty()) {
      const auto [v, prv] = q.front();
      q.pop();
      for (const auto u : g[v]) {
        if (u == prv) {
          continue;
        }
        if (dist[u] == -1) {
          dist[u] = dist[v] + 1;
          q.emplace(u, v);
        } else if (!grith.has_value() || dist[v] + dist[u] + 1 < grith) {
          grith = dist[v] + dist[u] + 1;
        }
      }
    }
  }
  println(grith.has_value() ? grith.value() : -1);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}