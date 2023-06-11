#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n, m; cin >> n >> m;
  vector<vector<int>> g(n);
  vector<pair<int, int>> es(m);
  for (auto &[u, v] : es) {
    cin >> u >> v;
    --u, --v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }

  vector<int> comp(n, -1), comps, subtree_sz(n, 0), tin(n, -1);
  vector<bool> used(n, false);
  int timer = 0;
  auto dfs = [&](auto &f, int v) -> void {
    comp[v] = int(comps.size()) - 1;
    ++comps.back();
    subtree_sz[v] = 1;
    tin[v] = timer++;
    used[v] = true;
    for (auto u : g[v]) {
      if (used[u]) continue;
      f(f, u);
      subtree_sz[v] += subtree_sz[u];
    }
  };

  for (int v = 0; v < n; ++v) {
    if (used[v]) continue;
    comps.emplace_back(0);
    dfs(dfs, v);
  }

  int q; cin >> q;
  for (int i = 0; i < q; ++i) {
    int j; cin >> j; --j;
    auto [u, v] = es[j];
    if (tin[u] > tin[v]) swap(u, v);
    cout << 1ll * subtree_sz[v] * (comps[comp[u]] - subtree_sz[v]) << '\n';
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
