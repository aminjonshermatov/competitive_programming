#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
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

  vector<i64> sub(n, 0);
  i64 ans = 0;
  auto dfs = [&](auto &f, int v, int p) -> void {
    sub[v] = 1;
    for (auto u : g[v]) {
      if (u == p) continue;
      f(f, u, v);
      sub[v] += sub[u];
    }
    i64 lhs = 0;
    for (auto u : g[v]) {
      if (u == p) continue;
      ans += lhs * sub[u] * (n - lhs - sub[u] - 1);
      lhs += sub[u];
    }
  };
  dfs(dfs, 0, -1);
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
