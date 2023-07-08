#include <bits/stdc++.h>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

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
  vector<vector<int>> g(n);
  for (int i = 1; i < n; ++i) {
    int p; cin >> p;
    --p;
    g[p].emplace_back(i);
  }

  vector<int> dist(n, -1);
  for (int i = 0; i < m; ++i) {
    int v, d; cin >> v >> d;
    --v;
    dist[v] = max(dist[v], d);
  }

  priority_queue<pair<int, int>> pq;
  for (int v = 0; v < n; ++v) {
    if (dist[v] > 0) {
      pq.emplace(dist[v], v);
    }
  }

  while (!pq.empty()) {
    auto [d, v] = pq.top(); pq.pop();
    if (dist[v] > d) continue;

    for (auto u : g[v]) {
      if (dist[u] < d - 1) {
        dist[u] = d - 1;
        if (d - 1 > 0) {
          pq.emplace(d - 1, u);
        }
      }
    }
  }

  dbg(dist);
  int cnt = 0;
  for (int v = 0; v < n; ++v) {
    cnt += dist[v] != -1;
  }

  cout << cnt << '\n';
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
