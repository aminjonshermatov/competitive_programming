#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using i64 = int64_t;

void solve() {
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> g(n);
  std::vector<int> A(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> A[i];
  }
  for (int i = 0; i < m; ++i) {
    int b;
    std::cin >> b;
    g[A[i] - 1].emplace_back(b - 1);
    g[b - 1].emplace_back(A[i] - 1);
  }
  std::vector<int> col(n, -1);
  auto dfs = [&](auto &f, int v, int c) -> bool {
    col[v] = c;
    for (auto u : g[v]) {
      if (col[u] == -1) {
        col[u] = 1 ^ c;
        if (!f(f, u, 1 ^ c)) {
          return false;
        }
      } else if (col[u] != (1 ^ c)) {
        return false;
      }
    }
    return true;
  };
  for (int v = 0; v < n; ++v) {
    if (col[v] == -1 && !dfs(dfs, v, 0)) {
      std::cout << "No\n";
      return;
    }
  }
  std::cout << "Yes\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}