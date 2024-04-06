#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using i64 = int64_t;

void solve() {
  int n;
  std::cin >> n;
  std::vector<std::vector<int>> g(n);
  for (int i = 1; i < n; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }

  std::vector<i64> cs(n);
  for (auto& c : cs) {
    std::cin >> c;
  }
  std::vector<i64> sub(n);
  auto dfs_init = [&](auto&& self, int v, int p, int depth) -> i64 {
    sub[v] = cs[v];
    i64 loc = cs[v] * depth;
    for (auto u : g[v]) {
      if (u != p) {
        loc += self(self, u, v, depth + 1);
        sub[v] += sub[u];
      }
    }
    return loc;
  };
  i64 ret = std::numeric_limits<i64>::max() / 2;
  auto dfs = [&](auto&& self, int v, int p, i64 cur) -> void {
    ret = std::min(ret, cur);
    for (auto u : g[v]) {
      if (u == p) {
        continue;
      }
      self(self, u, v, cur + sub[0] - sub[u] * 2);
    }
  };
  dfs(dfs, 0, -1, dfs_init(dfs_init, 0, -1, 0));
  std::cout << ret << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}