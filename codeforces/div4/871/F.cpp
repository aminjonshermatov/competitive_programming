// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n, m; cin >> n >> m;
  vector<vector<int>> g(n);
  for (int i = 0; i < m; ++i) {
    int u, v; cin >> u >> v;
    --u, --v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }

  vector<int> sz(n, 0);
  vector<bool> used(n, false);
  auto dfs_sz =[&](auto &f, int v) -> void {
    sz[v] = 1;
    used[v] = true;
    for (auto u : g[v]) {
      if (used[u]) continue;
      f(f, u);
      sz[v] += sz[u];
    }
  };
  dfs_sz(dfs_sz, 0);
  auto centroid = [&](auto &f, int v) -> int {
    used[v] = true;
    for (auto u : g[v]) {
      if (used[u]) continue;
      if (sz[u] * 2 > n) return f(f, u);
    }
    return v;
  };
  fill(used.begin(), used.end(), false);
  auto c = centroid(centroid, 0);
  int x = g[c].size();
  int y = -1;
  for (auto u : g[c]) {
    if (y == -1) {
      y = g[u].size() - 1;
    } else {
      assert(y == g[u].size() - 1);
    }
  }
  cout << x << ' ' << y << '\n';
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
