#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

void solve() {
  int n, m; cin >> n >> m;
  vector<vector<pair<int, int>>> g(n);
  for (int i = 0; i < m; ++i) {
    int u, v, w; cin >> u >> v >> w;
    --u, --v;
    g[u].emplace_back(v, w);
    g[v].emplace_back(u, w);
  }
  i64 ans = 0;
  auto dfs = [&](auto &f, int v, int used, i64 cur) -> void {
    ans = max(ans, cur);
    for (auto [u, w] : g[v]) {
      if (used >> u & 1) continue;
      f(f, u, used | (1 << u), cur + w);
    }
  };
  for (int v = 0; v < n; ++v) {
    dfs(dfs, v, 1 << v, 0);
  }
  cout << ans << '\n';
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
