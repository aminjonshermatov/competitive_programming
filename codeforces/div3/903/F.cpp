#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

void solve() {
  int n, k;
  cin >> n >> k;
  vector<int> ks(k);
  for (auto &v : ks) {
    cin >> v;
    --v;
  }
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }

  const auto bfs = [&](int V) -> vector<int> {
    vector<int> dist(n, -1);
    queue<int> q;
    dist[V] = 0;
    q.emplace(V);
    while (!q.empty()) {
      auto v = q.front(); q.pop();
      for (auto u : g[v]) {
        if (dist[u] != -1) continue;
        dist[u] = dist[v] + 1;
        q.emplace(u);
      }
    }
    return dist;
  };

  const auto d1 = bfs(ks.front());
  int v1 = -1;
  for (auto v : ks) {
    if (v1 == -1 || d1[v1] < d1[v]) {
      v1 = v;
    }
  }
  const auto d2 = bfs(v1);
  int v2 = -1;
  for (auto v : ks) {
    if (v2 == -1 || d2[v2] < d2[v]) {
      v2 = v;
    }
  }
  const auto d3 = bfs(v2);
  int ans = 1e9;
  for (int v = 0; v < n; ++v) {
    ans = min(ans, max(d2[v], d3[v]));
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
  return 0;
}
