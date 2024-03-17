#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  int n, m, k;
  std::cin >> n >> m >> k;
  std::vector<std::vector<std::pair<int, int>>> g(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    g[u].emplace_back(v, i);
    g[v].emplace_back(u, i);
  }

  std::vector<bool> used(n, false);
  std::vector<int> state(n, 0), ids;
  auto dfs = [&](auto&& self, int v) -> void {
    used[v] = true;
    for (auto [u, id] : g[v]) {
      if (used[u]) {
        continue;
      }
      self(self, u);
      if (k > 0 && state[u] == 0) {
        k += state[v] + state[u];
        state[v] ^= 1;
        state[u] ^= 1;
        k -= state[v] + state[u];
        ids.emplace_back(id + 1);
      }
    }
  };
  for (int v = 0; v < n; ++v) {
    if (!used[v]) {
      dfs(dfs, v);
    }
  }
  if (k != 0) {
    std::cout << "No\n";
    return;
  }
  std::cout << "Yes\n";
  std::cout << ids.size() << '\n';
  for (auto id : ids) {
    std::cout << id << ' ';
  }
  std::cout << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}