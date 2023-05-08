#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n, k; cin >> n >> k;
  vector<vector<int>> g(n);
  for (int i = 1; i < n; ++i) {
    int u, v; cin >> u >> v;
    --u, --v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }

  vector<int> sz(n, 0);
  auto dfs = [&](auto &f, int v, int p) -> void {
    sz[v] = 1;
    for (auto u : g[v]) {
      if (u == p) continue;
      f(f, u, v);
      sz[v] += sz[u];
    }

  };

  dfs(dfs, 0, -1);
}

bool is_multi = true;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
  return 0;
}
