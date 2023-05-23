#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

constexpr auto  inf = (int64_t)1e18;
constexpr auto ninf = -inf;

void solve() {
  int n, m; cin >> n >> m;
  vector<tuple<int, int, int64_t>> es(m);
  for (auto &[v, u, w] : es) {
    cin >> v >> u >> w;
    --v, --u;
  }

  vector<int64_t> dist(n, ninf);
  dist[0] = 0;
  for (int i = 0; i < n; ++i) {
    for (auto [u, v, w] : es) {
      dist[v] = min(max(dist[v], dist[u] + w), inf);
    }
  }

  for (auto [u, v, w] : es) {
    if (dist[v] < dist[u] + w) {
      dist[v] = inf;
    }
  }

  for (int i = 0; i < n; ++i) {
    for (auto [u, v, w] : es) {
      dist[v] = min(max(dist[v], dist[u] + w), inf);
    }
  }

  if (dist[n - 1] == inf) {
    cout << "inf\n";
    return;
  }
  cout << dist[n - 1] << '\n';
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
