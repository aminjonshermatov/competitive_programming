#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n, d; cin >> n >> d;
  vector<pair<int, int>> A(n);
  for (auto &[x, y] : A) cin >> x >> y;
  vector<vector<int>> g(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i == j) continue;
      auto dx = abs(A[i].first - A[j].first);
      auto dy = abs(A[i].second - A[j].second);
      auto dd = dx * dx + dy * dy;
      if (d * d >= dd) {
        g[i].emplace_back(j);
      }
    }
  }
  queue<int> q;
  vector<bool> used(n, false);
  q.emplace(0);
  used[0] = true;
  while (!q.empty()) {
    auto v = q.front(); q.pop();
    for (auto u : g[v]) {
      if (used[u]) continue;
      used[u] = true;
      q.emplace(u);
    }
  }
  for (int i = 0; i < n; ++i) {
    cout << (used[i] ? "Yes" : "No") << '\n';
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
