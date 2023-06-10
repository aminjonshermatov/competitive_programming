#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n; cin >> n;
  vector<vector<int>> g(n);
  for (int v = 1; v < n; ++v) {
    int u; cin >> u;
    --u;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }

  auto bfs = [&](int s) -> vector<int> {
    vector<int> dist(n, -1);
    queue<int> q;
    q.emplace(s);
    dist[s] = 0;
    while (!q.empty()) {
      auto v = q.front(); q.pop();
      for (auto u : g[v]) {
        if (dist[u] == -1) {
          dist[u] = dist[v] + 1;
          q.emplace(u);
        }
      }
    }
    return dist;
  };

  auto d1 = bfs(0);
  auto d2 = bfs(int(max_element(d1.begin(), d1.end()) - d1.begin()));
  auto d3 = bfs(int(max_element(d2.begin(), d2.end()) - d2.begin()));
  int mn = numeric_limits<int>::max();
  for (int v = 0; v < n; ++v) {
    mn = min(mn, max(d2[v], d3[v]));
  }

  for (int v = 0; v < n; ++v) {
    if (max(d2[v], d3[v]) == mn) {
      cout << v + 1 << ' ';
    }
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
