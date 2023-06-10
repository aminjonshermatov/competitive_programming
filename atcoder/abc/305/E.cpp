#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n, m, k; cin >> n >> m >> k;
  vector<vector<int>> g(n);
  for (int i = 0; i < m; ++i) {
    int u, v; cin >> u >> v;
    --u, --v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }

  vector<int> seen(n, 0);
  priority_queue<pair<int, int>> pq;
  for (int i = 0; i < k; ++i) {
    int p, h; cin >> p >> h;
    --p;
    seen[p] = h + 1;
    pq.emplace(h, p);
  }

  while (!pq.empty()) {
    auto [h, v] = pq.top(); pq.pop();
    for (auto u : g[v]) {
      if (seen[u] < h) {
        seen[u] = h;
        if (h > 0) pq.emplace(h - 1, u);
      }
    }
  }

  vector<int> ans;
  for (int v = 0; v < n; ++v) {
    if (seen[v] > 0) {
      ans.emplace_back(v);
    }
  }
  cout << ans.size() << '\n';
  for (auto v : ans) {
    cout << v + 1 << ' ';
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
