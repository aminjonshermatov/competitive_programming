#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

struct Point {
  int I{-1}, J{-1};
};

void Solve() {
  int n, m;
  Scan(n, m);
  auto ok = [n, m](int i, int j) {
    return std::clamp(i, 0, n - 1) == i && std::clamp(j, 0, m - 1) == j;
  };
  std::vector<std::string> g(n);
  Point start{}, goal{};
  for (int i = 0; i < n; ++i) {
    Scan(g[i]);
    if (const int j = g[i].find('S'); j != std::string::npos) {
      assert(start.I == start.J && start.I == -1);
      start = {i, j};
    }
    if (const int j = g[i].find('G'); j != std::string::npos) {
      assert(goal.I == goal.J && goal.I == -1);
      goal = {i, j};
    }
  }
  assert(start.I != -1 && start.I != -1);
  assert(goal.I != -1 && goal.I != -1);

  using T = std::tuple<int, int, int, int>;
  std::priority_queue<T, std::vector<T>, std::greater<>> pq;
  constexpr auto kInf = std::numeric_limits<int>::max() / 3;
  std::vector dist(n, std::vector(m, std::vector(2, kInf)));
  for (const auto isVertical : {0, 1}) {
    pq.emplace(dist[start.I][start.J][isVertical] = 0, start.I, start.J, isVertical);
  }
  while (!pq.empty()) {
    const auto [d, i, j, isV] = pq.top();
    pq.pop();
    if (d != dist[i][j][isV]) {
      continue;
    }
    if (isV == 1) {
      for (const auto di : {-1, +1}) {
        const auto ni = i + di;
        if (!ok(ni, j) || g[ni][j] == '#') {
          continue;
        }
        if (dist[ni][j][0] > d + 1) {
          pq.emplace(dist[ni][j][0] = d + 1, ni, j, 0);
        }
      }
    } else {
      for (const auto dj : {-1, +1}) {
        const auto nj = j + dj;
        if (!ok(i, nj) || g[i][nj] == '#') {
          continue;
        }
        if (dist[i][nj][1] > d + 1) {
          pq.emplace(dist[i][nj][1] = d + 1, i, nj, 1);
        }
      }
    }
  }
  const auto best = std::ranges::min(dist[goal.I][goal.J]);
  Println(best == kInf ? -1 : best);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
