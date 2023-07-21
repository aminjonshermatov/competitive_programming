#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 =  int64_t;
using u64 = uint64_t;

constexpr i64 step = (i64(2e9) + 100) * 2e5;
constexpr i64 ninf = numeric_limits<i64>::min();

void solve() {
  int n, m; cin >> n >> m;
  vector<vector<pair<int, int>>> g(n);
  for (int i = 0; i < m; ++i) {
    int a, b, d;
    cin >> a >> b >> d;
    --a, --b;
    g[a].emplace_back(b, d);
    g[b].emplace_back(a, -d);
  }


  vector<i64> dist(n);
  vector<bool> seen(n, false);
  auto dfs = [&](auto &f, int v) -> bool {
    for (auto [u, d] : g[v]) {
      if (!seen[u]) {
        dist[u] = dist[v] + d;
        seen[u] = true;
        if (!f(f, u)) {
          return false;
        }
      } else if (dist[v] + d != dist[u]) {
        return false;
      }
    }
    return true;
  };
  for (int v = 0; v < n; ++v) {
    if (!seen[v]) {
      dist[v] = 0;
      seen[v] = true;
      if (!dfs(dfs, v)) {
        cout << "No\n";
        return;
      }
    }
  }
  cout << "Yes\n";
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
