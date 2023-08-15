#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

constexpr int NAX = 5e4 + 10;

void solve() {
  int n, m; cin >> n >> m;
  vector<vector<int>> ig(n);
  vector<int> deg(n, 0);
  for (int i = 0; i < m; ++i) {
    int u, v; cin >> u >> v;
    --u, --v;
    ig[v].emplace_back(u);
    ++deg[u];
  }
  vector<bitset<NAX>> can_reach(n);
  queue<int> q;
  for (int v = 0; v < n; ++v) {
    if (deg[v] == 0) {
      q.emplace(v);
    }
  }
  while (!q.empty()) {
    auto v = q.front(); q.pop();
    can_reach[v][v] = true;
    for (auto u : ig[v]) {
      can_reach[u] |= can_reach[v];
      if (--deg[u] == 0) {
        q.emplace(u);
      }
    }
  }
  for (int v = 0; v < n; ++v) {
    cout << can_reach[v].count() << ' ';
  }
  cout << '\n';
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
