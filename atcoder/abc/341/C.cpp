#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  int h, w, n;
  std::string t;
  std::cin >> h >> w >> n >> t;
  std::vector<std::string> g(h);
  for (auto& r : g) {
    std::cin >> r;
  }
  auto move = [&](std::pair<int, int>& cur, char cmd) -> void {
    switch (cmd) {
      case 'L': {
        --cur.second;
        return;
      }
      case 'R': {
        ++cur.second;
        return;
      }
      case 'D': {
        ++cur.first;
        return;
      }
      case 'U': {
        --cur.first;
        return;
      }
      default: assert(false);
    }
  };
  auto ok = [&](const std::pair<int, int>& p) -> bool {
    return std::clamp(p.first, 0, h - 1) == p.first && std::clamp(p.second, 0, w - 1) == p.second;
  };
  auto bfs = [&](std::pair<int, int> cur) -> std::optional<std::pair<int, int>> {
    for (auto c : t) {
      move(cur, c);
      if (!ok(cur) || g[cur.first][cur.second] == '#') {
        return std::nullopt;
      }
    }
    return cur;
  };
  std::set<std::pair<int, int>> all;
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      if (g[i][j] == '.') {
        auto qwe = bfs(std::pair(i, j));
        if (qwe.has_value()) {
          all.emplace(qwe.value());
        }
      }
    }
  }
  std::cout << all.size() << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}