#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

constexpr int N = 100100;
vector<int> g[N];
int X[N], seen[N];

void solve() {
  int n, m, k; cin >> n >> m >> k;
  for (int i = 1; i <= n; ++i) {
    g[i].clear();
  }
  memset(seen, 0, sizeof (seen));

  priority_queue<pair<int, int>> pq;
  for (int i = 0; i < k; ++i) {
    cin >> X[i];
  }
  for (int i = 0; i < k; ++i) {
    int d; cin >> d;
    if (d > 1) pq.emplace(d - 1, X[i]);
    seen[X[i]] = d;
  }

  for (int i = 0; i < m; ++i) {
    int u, v; cin >> u >> v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }
  while (!pq.empty()) {
    auto [d, v] = pq.top(); pq.pop();
    for (auto u : g[v]) {
      if (seen[u] < d) {
        seen[u] = d;
        if (d > 1) {
          pq.emplace(d - 1, u);
        }
      }
    }
  }
  for (int v = 1; v <= n; ++v) {
    if (!seen[v]) {
      cout << "NO\n";
      return;
    }
  }
  cout << "YES\n";
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
