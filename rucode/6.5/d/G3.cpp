#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

void solve() {
  int n; cin >> n;
  vector<vector<int>> g(n);
  for (int i = 1; i < n; ++i) {
    int p; cin >> p;
    --p;
    g[p].emplace_back(i);
    g[i].emplace_back(p);
  }

  vector<i64> sz(n, 0), dp(n, 0);
  auto dfs = [&](auto &f, int v, int p) -> void {
    sz[v] = 1;
    for (auto u : g[v]) {
      if (u == p) continue;
      f(f, u, v);
      sz[v] += sz[u];
      dp[v] += dp[u];
    }
    dp[v] += sz[v];
  };
  dfs(dfs, 0, -1);
  for (int v = 0; v < n; ++v) {
    cout << dp[v] << " \n"[v + 1 == n];
  }
}

bool is_multi = false;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
  return 0;
}
