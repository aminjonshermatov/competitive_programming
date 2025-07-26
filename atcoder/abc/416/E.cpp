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
  constexpr auto kInf = std::numeric_limits<int64_t>::max() / 3;
  std::vector dist(n, std::vector(n, kInf));
  for (int i = 0; i < n; ++i) {
    dist[i][i] = 0;
  }
  for (int i = 0; i < m; ++i) {
    int u, v;
    int64_t w;
    Scan(u, v, w);
    --u, --v;

    dist[u][v] = std::min(dist[u][v], w);
    dist[v][u] = std::min(dist[v][u], w);
  }

  int nk;
  int64_t t;
  Scan(nk, t);
  std::set<int> ds;
  for (int i = 0; i < nk; ++i) {
    int v;
    Scan(v);
    --v;
    ds.emplace(v);
  }
  for (auto u : ds) {
    for (auto v : ds) {
      dist[u][v] = std::min(dist[u][v], t);
    }
  }

  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }

  auto get = [&] {
    auto cur = 0LL;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        cur += dist[i][j] == kInf ? 0 : dist[i][j];
      }
    }
    return cur;
  };


  int q;
  Scan(q);
  while (q-- > 0) {
    char cmd;
    Scan(cmd);

    if (cmd == '1') {
      int u, v;
      int64_t w;
      Scan(u, v, w);
      --u, --v;

      dist[u][v] = std::min(dist[u][v], w);
      dist[v][u] = std::min(dist[v][u], w);

      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          dist[i][j] = std::min(dist[i][j], dist[i][u] + w + dist[v][j]);
          dist[i][j] = std::min(dist[i][j], dist[i][v] + w + dist[u][j]);
        }
      }
    } else if (cmd == '2') {
      int x;
      Scan(x);
      --x;

      for (auto u : ds) {
        dist[x][u] = std::min(dist[x][u], t);
        dist[u][x] = std::min(dist[u][x], t);
      }

      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          dist[x][i] = std::min(dist[x][i], dist[x][j] + dist[j][i]);
          dist[i][x] = std::min(dist[i][x], dist[i][j] + dist[j][x]);
        }
      }

      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          dist[i][j] = std::min(dist[i][j], dist[i][x] + dist[x][j]);
        }
      }
      ds.emplace(x);
    } else {
      Println(get());
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);


  Solve();
}
