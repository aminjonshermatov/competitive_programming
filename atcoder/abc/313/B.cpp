#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n, m; cin >> n >> m;
  vector<int> deg(n, 0);
  vector<vector<int>> g(n);
  for (int i = 0; i < m; ++i) {
    int a, b; cin >> a >> b;
    --a, --b;
    g[a].emplace_back(b);
    ++deg[b];
  }
  queue<int> q;
  vector<int> ord;
  for (int v = 0; v < n; ++v) {
    if (deg[v] == 0) {
      q.emplace(v);
    }
  }
  if (q.size() != 1) {
    cout << -1 << '\n';
    return;
  }
  while (!q.empty()) {
    auto v = q.front(); q.pop();
    ord.emplace_back(v);
    for (auto u : g[v]) {
      if (--deg[u] == 0) {
        q.emplace(u);
      }
    }
  }
  if (ord.size() != n) {
    cout << -1 << '\n';
    return;
  }
  cout << ord.front() + 1 << '\n';
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
