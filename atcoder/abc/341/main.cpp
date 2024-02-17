#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> g(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }
  std::vector<int> ws(n), as(n);
  for (auto& w : ws) {
    std::cin >> w;
  }
  for (auto& a : as) {
    std::cin >> a;
  }
  for (auto& r : g) {
    std::ranges::sort(r, [&](int i, int j) {
      return ws[i] < ws[j];
    });
  }
  std::vector<bool> used(n, false);
  auto dfs = [&](auto& f, int v) -> int {
    int loc = 0, sum = 0;
    bool any = false;
    for (auto u : g[v]) {
      if (used[u]) {
        continue;
      }
      if (sum + ws[u] >= ws[v]) {
        break;
      }
      any |= true;
      sum += ws[u];
      used[u] = true;
      loc += f(f, u);
    }
    if (!any) {
      loc = 1;
    }
    return loc;
  };
  int loc = 0;
  for (int v = 0; v < n; ++v) {
    std::fill(used.begin(), used.end(), false);
    used[v] = true;
    loc += dfs(dfs, v) * as[v];
  }
  std::cout << loc << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}