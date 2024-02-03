#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

struct Point {
  int i = -1, j = -1;
  bool operator==(const Point& other) const {
    return i == other.i && j == other.j;
  }
  bool operator!=(const Point& other) const {
    return !(*this == other);
  }
};

void solve() {
  int n;
  std::cin >> n;
  std::vector<std::string> g(n);
  Point p1{}, p2{};
  for (int i = 0; i < n; ++i) {
    std::cin >> g[i];
    auto j = g[i].find('P');
    if (j != std::string::npos) {
      (p1.i == -1 ? p1 : p2) = {i, int(j)};
    }
  }

  auto ok = [n, &g](Point p) {
    return std::clamp(p.i, 0, n - 1) == p.i && std::clamp(p.j, 0, n - 1) == p.j && g[p.i][p.j] == '.';
  };

  std::array dk{1, 0, -1, 0, 1};
  auto bfs = [&](Point X, std::vector<std::vector<int>>& d) -> void {
    std::queue<Point> q;
    q.emplace(X);
    d[X.i][X.j] = 0;
    while (!q.empty()) {
      auto [i, j] = q.front();
      q.pop();
      for (int k = 0; k < 4; ++k) {
        auto ni = i + dk[k];
        auto nj = j + dk[k + 1];
        auto nd = Point{ni, nj};
        if (!ok(nd) || d[ni][nj] != -1) {
          continue;
        }
        d[ni][nj] = d[i][j] + 1;
        q.emplace(nd);
      }
    }
  };

  std::vector d1(n, std::vector<int>(n, -1)), d2(n, std::vector<int>(n, -1));
  bfs(p1, d1);
  bfs(p2, d2);
  int best = 1e9;
  for (int i = 0; i < n; ++i) {
    best = std::min(best, std::max(d1[0][i], d2[0][i]));
    best = std::min(best, std::max(d1[n - 1][i], d2[n - 1][i]));
    best = std::min(best, std::max(d1[i][0], d2[i][0]));
    best = std::min(best, std::max(d1[i][n - 1], d1[i][n - 1]));
  }
  std::cout << (best == 1e9 ? -1 : best) << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}