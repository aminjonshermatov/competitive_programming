#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

void solve() {
  int n;
  cin >> n;
  vector<vector<pair<int, int>>> g(n);
  for (int v = 0; v < n; ++v) {
    for (int u = v + 1; u < n; ++u) {
      int w;
      cin >> w;
      g[v].emplace_back(u, w);
    }
  }

  vector<i64> cache(1 << (n + 1), -1);
  auto dfs = [&](auto &f, int used) -> i64 {
    if (~cache[used]) return cache[used];
    i64 loc = 0;
    for (int v = 0; v < n; ++v) {
      if (used >> v & 1) continue;
      for (auto [u, w] : g[v]) {
        if (used >> u & 1) continue;
        loc = max(loc, f(f, used | (1 << v) | (1 << u)) + w);
      }
    }
    return cache[used] = loc;
  };
  cout << dfs(dfs, 0) << '\n';
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
