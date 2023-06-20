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
    int u, v; cin >> u >> v;
    --u, --v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }

  vector<int> leafs(n, 0);
  auto dfs = [&](auto &f, int v, int p) -> void {
    for (auto u : g[v]) {
      if (u != p) {
        f(f, u, v);
      }
    }
    if (g[v].size() == 1 && g[v].front() == p) {
      leafs[v] = 1;
    } else {
      for (auto u : g[v]) {
        if (u == p) continue;
        leafs[v] += leafs[u];
      }
    }
  };

  dfs(dfs, 0, -1);
  int q; cin >> q;
  while (q--) {
    int x, y; cin >> x >> y;
    --x, --y;
    cout << 1ll * leafs[x] * leafs[y] << '\n';
  }
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
