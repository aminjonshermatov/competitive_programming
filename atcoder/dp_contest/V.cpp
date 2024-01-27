#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  int n, mod;
  std::cin >> n >> mod;
  std::vector<std::vector<int>> g(n);
  for (int i = 1; i < n; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }

  auto add = [&](int a, int b) -> int { return (a + b) % mod; };
  auto mul = [&](int a, int b) -> int { return (a * 1ll * b) % mod; };

  int V = -1;
  for (int v = 0; v < n && V == -1; ++v) {
    if (g[v].size() == 1) {
      V = v;
    }
  }

  std::vector<int> dp_down(n, 1);
  auto dfs_down = [&](auto& f, int v, int p) -> void {
    for (auto u : g[v]) {
      if (u == p) {
        continue;
      }
      f(f, u, v);
      dp_down[v] = mul(dp_down[v], dp_down[u] + 1);
    }
  };
  dfs_down(dfs_down, V, -1);
  std::vector<int> dp_up(n, 1);
  auto dfs_up = [&](auto& f, int v, int p) -> void {
    const auto m = int(g[v].size());
    std::vector<int> pref(m), suf(m);
    for (int i = 0; i < m; ++i) {
      pref[i] = mul(i > 0 ? pref[i - 1] : 1, g[v][i] == p ? 1 : (dp_down[g[v][i]] + 1));
      suf[m - 1 - i] = mul(m - i < m ? suf[m - i] : 1, g[v][m - 1 - i] == p ? 1 : (dp_down[g[v][m - 1 - i]] + 1));
    }
    for (int i = 0; i < m; ++i) {
      if (g[v][i] == p) {
        continue;
      }
      dp_up[g[v][i]] = add(mul(dp_up[v], mul(i > 0 ? pref[i - 1] : 1, i + 1 < m ? suf[i + 1] : 1)), 1);
      f(f, g[v][i], v);
    }
  };
  dfs_up(dfs_up, V, -1);
  dbg(V);
  dbg(dp_down);
  dbg(dp_up);
  for (int v = 0; v < n; ++v) {
    std::cout << mul(dp_down[v], dp_up[v]) << ' ';
  }
  std::cout << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}