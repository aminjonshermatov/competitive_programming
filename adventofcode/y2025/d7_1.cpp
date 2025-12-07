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
  std::vector<std::string> g;
  for (std::string s; ; s.clear()) {
    std::getline(std::cin, s);
    if (s.empty()) {
      break;
    }
    g.emplace_back(s);
  }
  const auto n = int(g.size());
  const int m = std::ranges::max(g, {}, &std::string::size).size();
  for (auto& s : g) {
    assert(s.size() == m);
  }

  std::queue<std::pair<int, int>> que;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (g[i][j] == 'S') {
        assert(que.empty());
        que.emplace(i, j);
      }
    }
  }
  auto ok = [n, m](const int i, const int j) {
    return std::clamp(i, 0, n - 1) == i && std::clamp(j, 0, m - 1) == j;
  };
  auto ret = 0;
  while (!que.empty()) {
    const auto [i, j] = que.front();
    que.pop();
    if (!ok(i + 1, j)) {
      break;
    }
    if (g[i + 1][j] == '.') {
      g[i + 1][j] = '|';
      que.emplace(i + 1, j);
    } else if (g[i + 1][j] == '^') {
      ++ret;
      if (ok(i + 1, j - 1) && g[i + 1][j - 1] == '.') {
        g[i + 1][j - 1] = '|';
        que.emplace(i + 1, j - 1);
      }
      if (ok(i + 1, j + 1) && g[i + 1][j + 1] == '.') {
        g[i + 1][j + 1] = '|';
        que.emplace(i + 1, j + 1);
      }
    }
  }
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
