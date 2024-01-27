#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  int n, m;
  std::cin >> n >> m;
  using i64 = int64_t;
  constexpr auto inf = std::numeric_limits<i64>::max() / 2;
  std::vector adj(n, std::vector<i64>(n, inf));
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    std::cin >> u >> v >> w;
    adj[--u][--v] = w;
  }
  for (int v = 0; v < n; ++v) {
    adj[v][v] = 0;
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      for (int k = 0; k < n; ++k) {
        if (adj[i][k] == inf || adj[k][j] == inf) {
          continue;
        }
        adj[i][j] = std::min(adj[i][j], adj[i][k] + adj[k][j]);
      }
    }
  }

  std::vector dp(1 << n, std::vector<i64>(n, inf));
  for (int v = 0; v < n; ++v) {
    dp[1 << v][v] = 0;
  }
  for (int mask = 1; mask < (1 << n); ++mask) {
    for (int tmp = mask, u; tmp > 0; tmp ^= 1 << u) {
      u = 31 - __builtin_clz(tmp);
      if (dp[mask][u] == inf) {
        continue;
      }
      assert(tmp >> u & 1);
      for (int v = 0; v < n; ++v) {
        auto& nxt = dp[mask | (1 << v)][v];
        if (adj[u][v] == inf) {
          continue;
        }
        nxt = std::min(nxt, dp[mask][u] + adj[u][v]);
      }
    }
  }
  auto best = std::ranges::min(dp[(1 << n) - 1]);
  if (best == inf) {
    std::cout << "No";
  } else {
    std::cout << best;
  }
  std::cout << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}