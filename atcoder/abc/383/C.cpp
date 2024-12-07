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
  int n, m, d;
  Scan(n, m, d);
  std::vector<std::string> g(n);
  for (int i = 0; i < n; ++i) {
    Scan(g[i]);
  }
  auto ok = [n, m](int i, int j) {
    return std::clamp(i, 0, n - 1) == i && std::clamp(j, 0, m - 1) == j;
  };
  constexpr std::array kDk{1, 0, -1, 0, 1};
  constexpr auto kInf = std::numeric_limits<int>::max() / 3;
  std::vector dist(n, std::vector(m, kInf));
  using T = std::tuple<int, int, int>;
  std::priority_queue<T, std::vector<T>, std::greater<>> pq;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (g[i][j] == 'H') {
        pq.emplace(dist[i][j] = 0, i, j);
      }
    }
  }
  while (!pq.empty()) {
    const auto [curD, i, j] = pq.top();
    pq.pop();
    if (curD != dist[i][j]) {
      continue;
    }
    for (int k = 0; k < 4; ++k) {
      const auto ni = i + kDk[k];
      const auto nj = j + kDk[k + 1];
      if (ok(ni, nj) && g[ni][nj] == '.' && curD + 1 < dist[ni][nj]) {
        pq.emplace(dist[ni][nj] = curD + 1, ni, nj);
      }
    }
  }
  int tot = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      tot += static_cast<int>(dist[i][j] <= d);
    }
  }
  Println(tot);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
