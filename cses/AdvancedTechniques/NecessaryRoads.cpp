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
  vector<pair<int, int>> es(m);
  for (int i = 0; i < m; ++i) {
    auto &[u, v] = es[i];
    cin >> u >> v;
    --u, --v;
    g[u].emplace_back(i);
    g[v].emplace_back(i);
  }

  vector<int> tin(n), low(n), bs;
  vector<bool> used(n, false);
  int timer = 0;
  auto dfs = [&](auto &f, int v, int p) -> void {
    used[v] = true;
    tin[v] = low[v] = timer++;
    for (auto i : g[v]) {
      auto u = es[i].first ^ es[i].second ^ v;
      if (u == p) continue;
      if (used[u]) {
        low[v] = min(low[v], tin[u]);
      } else {
        f(f, u, v);
        low[v] = min(low[v], low[u]);
        if (low[u] > tin[v]) {
          bs.emplace_back(i);
        }
      }
    }
  };
  for (int v = 0; v < n; ++v) {
    if (!used[v]) {
      dfs(dfs, v, -1);
    }
  }
  cout << bs.size() << '\n';
  for (auto i : bs) {
    cout << es[i].first + 1 << ' ' << es[i].second + 1 << '\n';
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
