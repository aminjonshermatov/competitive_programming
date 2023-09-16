#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

void solve() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> g(n);
  struct Point {
    i64 x, y;
  };
  struct Edge {
    int u, v;
    Point pt;
  };
  vector<Edge> es(m);
  for (int i = 0; auto &[u, v, pt] : es) {
    cin >> u >> v >> pt.x >> pt.y;
    --u, --v;
    g[u].emplace_back(i);
    g[v].emplace_back(i);
    ++i;
  }


  vector<Point> dist(n);
  dist[0] = {0, 0};
  vector<bool> seen(n, false);
  const auto dfs = [&](auto &f, int v) -> void {
    seen[v] = true;
    for (auto id : g[v]) {
      auto u = es[id].v ^ es[id].u ^ v;
      if (seen[u]) continue;
      i64 sx = 1, sy = 1;
      if (u == es[id].u) {
        sx = sy = -1;
      }
      dist[u].x = dist[v].x + es[id].pt.x * sx;
      dist[u].y = dist[v].y + es[id].pt.y * sy;
      f(f, u);
    }
  };
  dfs(dfs, 0);

  for (int v = 0; v < n; ++v) {
    if (seen[v]) {
      cout << dist[v].x << ' ' << dist[v].y << '\n';
    } else {
      cout << "undecidable\n";
    }
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
