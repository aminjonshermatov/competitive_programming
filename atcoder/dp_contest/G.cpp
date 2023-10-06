#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> g(n);
  vector deg(n, 0);
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    g[u].emplace_back(v);
    ++deg[v];
  }

  queue<int> q;
  for (int v = 0; v < n; ++v) {
    if (deg[v] == 0) {
      q.emplace(v);
    }
  }

  vector<int> ord;
  ord.reserve(n);
  while (!q.empty()) {
    auto v = q.front();
    q.pop();
    ord.emplace_back(v);
    for (auto u : g[v]) {
      if (--deg[u] == 0) {
        q.emplace(u);
      }
    }
  }
  reverse(ord.begin(), ord.end());
  vector dp(n, -1);
  for (auto v : ord) {
    dp[v] = 0;
    for (auto u : g[v]) {
      dp[v] = max(dp[v], dp[u] + 1);
    }
  }
  cout << *max_element(dp.begin(), dp.end()) << '\n';
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
