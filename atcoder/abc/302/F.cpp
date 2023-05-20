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
  int n, m; cin >> n >> m;
  vector<vector<int>> g(m);
  vector<vector<int>> A(n);
  for (int i = 0; i < n; ++i) {
    int c; cin >> c;
    A[i].resize(c);
    for (int j = 0; j < c; ++j) {
      cin >> A[i][j];
      g[--A[i][j]].emplace_back(i);
    }
  }

  vector<int> dist(n, -1);
  queue<int> q;
  for (auto u : g[0]) {
    dist[u] = 0;
    q.emplace(u);
  }
  while (!q.empty()) {
    auto v = q.front(); q.pop();
    for (auto lev : A[v]) {
      for (auto u : g[lev]) {
        if (dist[u] == -1) {
          dist[u] = dist[v] + 1;
          q.emplace(u);
        }
      }
    }
  }
  int ans = 1e9;
  for (auto u : g[m - 1]) {
    ans = min(ans, dist[u]);
  }
  cout << (ans == 1e9 ? -1 : ans) << '\n';
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
