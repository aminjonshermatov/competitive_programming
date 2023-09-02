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
  int a, b, c;
  cin >> n >> m >> a >> b >> c;
  --a, --b, --c;
  vector<vector<int>> g(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }

  vector<int> state(n, 0);
  auto bfs = [&](int V, int s) -> void {
    queue<int> q;
    q.emplace(V);
    state[V] |= 1 << s;
    while (!q.empty()) {
      auto v = q.front();
      q.pop();
      for (auto u : g[v]) {
        if (state[u] >> s & 1) continue;
        if (u == (a ^ c ^ V)) continue;
        state[u] |= 1 << s;
        q.emplace(u);
      }
    }
  };

  bfs(a, 0);
  bfs(c, 1);

  bool ok = false;
  for (auto v : g[b]) {
    for (auto u : g[b]) {
      if (u == v) continue;
      ok |= (state[u] | state[v]) == 3;
    }
  }

  cout << (ok ? "Yes" : "No") << '\n';
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
