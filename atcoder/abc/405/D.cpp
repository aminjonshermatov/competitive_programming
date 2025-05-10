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

  constexpr auto kInf = std::numeric_limits<int>::max() / 2;
  std::vector dist(n, std::vector(m, kInf));
  std::vector type(n, std::string(m, '#'));
  using T = std::tuple<int, int, int>;
  std::priority_queue pq(std::greater<T>{}, std::vector<T>{});

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (g[i][j] == 'E') {
        pq.emplace(dist[i][j] = 0, i, j);
      }
    }
  }
  auto ok = [n, m](const int i, const int j) {
    return std::clamp(i, 0, n - 1) == i && std::clamp(j, 0, m - 1) == j;
  };
  auto getDir = [](const int di, const int dj) {
    assert(di * di + dj * dj == 1);
    if (di == 0) {
      return dj == -1 ? '>' : '<';
    }
    return di == -1 ? 'v' : '^';
  };
  std::array dk{1, 0, -1, 0, 1};
  while (!pq.empty()) {
    const auto [d, i, j] = pq.top();
    pq.pop();
    if (d != dist[i][j]) {
      continue;
    }
    for (int k = 0; k < 4; ++k) {
      const auto ni = i + dk[k];
      const auto nj = j + dk[k + 1];
      if (ok(ni, nj) && g[ni][nj] == '.' && dist[ni][nj] > dist[i][j] + 1) {
        pq.emplace(dist[ni][nj] = dist[i][j] + 1, ni, nj);
        type[ni][nj] = getDir(dk[k], dk[k + 1]);
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (g[i][j] == '.') {
        g[i][j] = type[i][j];
      }
    }
    Println(g[i]);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
