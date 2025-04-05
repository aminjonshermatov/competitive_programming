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
  std::vector<std::string> g(n);
  for (int i = 0; i < n; ++i) {
    Scan(g[i]);
  }
  int a, b, c, d;
  Scan(a, b, c, d);
  --a, --b, --c, --d;

  using T = std::tuple<int, int, int>;
  std::priority_queue pq(std::greater<T>{}, std::vector<T>{});
  constexpr auto kInf = std::numeric_limits<int>::max() / 2;
  std::vector dist(n, std::vector(m, kInf));
  pq.emplace(dist[a][b] = 0, a, b);

  constexpr std::array kDk{1, 0, -1, 0, 1};
  auto ok = [n, m](int i, int j) {
    return std::clamp(i, 0, n - 1) == i && std::clamp(j, 0, m - 1) == j;
  };
  while (!pq.empty()) {
    const auto [x, i, j] = pq.top();
    pq.pop();
    assert(x >= dist[i][j]);
    if (x != dist[i][j]) {
      continue;
    }
    for (int k = 0; k < 4; ++k) {
      const auto ni = i + kDk[k];
      const auto nj = j + kDk[k + 1];
      if (!ok(ni, nj)) {
        continue;
      }
      if (g[ni][nj] == '.') {
        if (x < dist[ni][nj]) {
          pq.emplace(dist[ni][nj] = x, ni, nj);
        }
      } else if (g[ni][nj] == '#') {
        if (x + 1 < dist[ni][nj]) {
          pq.emplace(dist[ni][nj] = x + 1, ni, nj);
        }
        const auto nni = ni + kDk[k];
        const auto nnj = nj + kDk[k + 1];
        if (ok(nni, nnj) && x + 1 < dist[nni][nnj]) {
          pq.emplace(dist[nni][nnj] = x + 1, nni, nnj);
        }
      }
    }
  }
  Println(dist[c][d]);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
