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
  int p, q;
  Scan(n, m, x, p, q);
  --p, --q;
  std::vector g(n, std::vector(m, int64_t{}));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      Scan(g[i][j]);
    }
  }

  auto ok = [n, m](int i, int j) {
    return std::clamp(i, 0, n - 1) == i && std::clamp(j, 0, m - 1) == j;
  };
  constexpr std::array kDk{1, 0, -1, 0, 1};
  using T = std::tuple<__int128, int, int>;
  std::priority_queue<T, std::vector<T>, std::greater<>> pq;
  auto cur = g[p][q];
  g[p][q] = -1;
  for (int k = 0; k < 4; ++k) {
    const auto ni = p + kDk[k];
    const auto nj = q + kDk[k + 1];
    if (ok(ni, nj)) {
      pq.emplace(__int128(x) * g[ni][nj], ni, nj);
    }
  }
  while (!pq.empty() && std::get<0>(pq.top()) < cur) {
    const auto [val, i, j] = pq.top();
    pq.pop();
    if (g[i][j] == -1) {
      continue;
    }
    assert(val < cur);
    cur += g[i][j];
    g[i][j] = -1;
    for (int k = 0; k < 4; ++k) {
      const auto ni = i + kDk[k];
      const auto nj = j + kDk[k + 1];
      if (ok(ni, nj) && g[ni][nj] != -1) {
        pq.emplace(__int128(x) * g[ni][nj], ni, nj);
      }
    }
  }
  Println(cur);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
