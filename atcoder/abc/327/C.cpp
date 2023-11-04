#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using i64 = int64_t;

void solve() {
  constexpr int N = 9;
  std::array<std::array<int, N>, N> g{};
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      std::cin >> g[i][j];
    }
  }

  bool ok = true;
  for (int i = 0; i < N; ++i) {
    std::set<int> set;
    for (int j = 0; j < N; ++j) {
      set.emplace(g[i][j]);
    }
    ok &= set.size() == 9 && *set.begin() == 1 && *set.rbegin() == 9;
  }
  for (int j = 0; j < N; ++j) {
    std::set<int> set;
    for (int i = 0; i < N; ++i) {
      set.emplace(g[i][j]);
    }
    ok &= set.size() == 9 && *set.begin() == 1 && *set.rbegin() == 9;
  }
  std::map<std::pair<int, int>, std::set<int>> vals{};
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      vals[std::pair(i / 3, j / 3)].emplace(g[i][j]);
    }
  }
  for (auto &[_, set] : vals) {
    ok &= set.size() == 9 && *set.begin() == 1 && *set.rbegin() == 9;
  }
  std::cout << (ok ? "Yes" : "No") << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}