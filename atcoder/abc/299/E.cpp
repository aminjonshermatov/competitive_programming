// #define _GLIBCXX_DEBUG
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
  for (int i = 0; i < m; ++i) {
    int u, v; cin >> u >> v;
    --u, --v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }

  int k; cin >> k;
  vector<pair<int, int>> pd(k);
  vector<bool> black(n, true);
  for (auto &[p, d] : pd) {
    cin >> p >> d, --p;

    queue<int> q;
    vector<int> dist(n, -1);
    q.emplace(p);
    dist[p] = 0;
    while (!q.empty()) {
      auto v = q.front(); q.pop();
      if (dist[v] < d) {
        black[v] = false;
      }
      for (auto u : g[v]) {
        if (dist[u] == -1) {
          dist[u] = dist[v] + 1;
          q.emplace(u);
        }
      }
    }
  }

  vector<int> dist(n, -1);
  queue<int> q;
  for (int v = 0; v < n; ++v) {
    if (black[v]) {
      dist[v] = 0;
      q.emplace(v);
    }
  }

  while (!q.empty()) {
    auto v = q.front(); q.pop();
    for (auto u : g[v]) {
      if (dist[u] == -1) {
        dist[u] = dist[v] + 1;
        q.emplace(u);
      }
    }
  }

  for (auto [p, d] : pd) {
    if (dist[p] != d) {
      cout << "No\n";
      return ;
    }
  }

  cout << "Yes\n";
  for (int v = 0; v < n; ++v) {
    cout << black[v];
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
