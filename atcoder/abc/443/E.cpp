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
  int n, c;
  Scan(n, c);
  --c;
  std::vector<std::string> g(n);
  for (int i = 0; i < n; ++i) {
    Scan(g[i]);
  }

  std::vector<std::pair<int, int>> que;
  std::vector vis(n, std::vector(n, false));
  std::vector can(n, 1);
  que.emplace_back(n - 1, c);
  vis[n - 1][c] = true;
  for (int r = n - 1; r >= 0; --r) {
    for (int col = 0; col < n; ++col) {
      can[col] &= g[r][col] == '.';
    }
    std::vector<std::pair<int, int>> nque;
    for (const auto [i, j] : que) {
      if (i == 0) {
        continue;
      }
      for (auto nj : {j - 1, j, j + 1}) {
        if (std::clamp(nj, 0, n - 1) != nj || vis[i - 1][nj]) {
          continue;
        }
        if (g[i - 1][nj] == '.' || can[nj]) {
          vis[i - 1][nj] = true;
          g[i - 1][nj] = '.';
          nque.emplace_back(i - 1, nj);
        }
      }
    }
    std::swap(que, nque);
  }
  for (int i = 0; i < n; ++i) {
    std::cout << char('0' + vis[0][i]);
  }
  Println();
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  Scan(t);
  while (t-- > 0) {
    Solve();
  }
}
