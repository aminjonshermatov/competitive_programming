#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using ll = long long;

void solve() {
  int n, k, c;
  cin >> n >> k >> c;
  vector<vector<int>> g(n);
  for (int i = 1; i < n; ++i) {
    int u, v; cin >> u >> v;
    --u, --v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }

  vector<int> dist(n);
  auto dfs = [&](auto f, int v, int p) -> void {
    for (auto u : g[v]) {
      if (u == p) continue ;
      dist[u] = dist[v] + 1;
      f(f, u, v);
    }
  };

  dist[0] = 0;
  dfs(dfs, 0, -1);
  auto from_root = dist;
  auto r2 = int(max_element(dist.begin(), dist.end()) - dist.begin());
  dist[r2] = 0;
  dfs(dfs, r2, -1);
  auto from_r2 = dist;
  auto r3 = int(max_element(dist.begin(), dist.end()) - dist.begin());
  dist[r3] = 0;
  dfs(dfs, r3, -1);
  auto from_r3 = dist;

  ll ans = 0;
  for (int v = 0; v < n; ++v) {
    ans = max(ans, 1ll * k * max(from_r2[v], from_r3[v]) - 1ll * c * from_root[v]);
  }
  cout << ans << '\n';
}

bool is_multi = true;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
}
