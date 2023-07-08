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
  int n1, n2, m; cin >> n1 >> n2 >> m;
  vector<vector<int>> g(n1 + n2);
  for (int i = 0; i < m; ++i) {
    int u, v; cin >> u >> v;
    --u, --v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }

  auto max_dist = [&](int S) -> int {
    vector<int> dist(g.size(), -1);
    queue<int> q;
    q.emplace(S);
    dist[S] = 0;
    while (!q.empty()) {
      auto v = q.front(); q.pop();
      for (auto u : g[v]) {
        if (dist[u] == -1) {
          dist[u] = dist[v] + 1;
          q.emplace(u);
        }
      }
    }
    return *max_element(dist.begin(), dist.end());
  };

  cout << max_dist(0) + 1 + max_dist(n1 + n2 - 1) << '\n';
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
