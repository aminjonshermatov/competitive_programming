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
  std::vector<std::string> adj(n);
  for (int i = 0; i < n; ++i) {
    Scan(adj[i]);
  }

  std::vector<std::pair<int, int>> que;
  constexpr auto kInf = std::numeric_limits<int>::max() / 3;
  std::vector dist(n, std::vector(n, kInf));
  auto push = [&](int i, int j, int d) {
    if (d < dist[i][j]) {
      dist[i][j] = d;
      que.emplace_back(i, j);
    }
  };
  for (int i = 0; i < n; ++i) {
    push(i, i, 0);
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i != j && adj[i][j] != '-') {
        push(i, j, 1);
      }
    }
  }
  for (std::size_t it{0}; it < que.size(); ++it) {
    auto [i, j] = que[it];
    for (int x = 0; x < n; ++x) {
      for (int y = 0; y < n; ++y) {
        if (adj[x][i] != '-' && adj[x][i] == adj[j][y]) {
          push(x, y, dist[i][j] + 2);
        }
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    std::ranges::replace(dist[i], kInf, -1);
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
