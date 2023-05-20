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
  int n, q; cin >> n >> q;
  vector<int> deg(n, 0);
  int cnt = n;
  vector<set<int>> g(n);
  while (q--) {
    char cmd; cin >> cmd;
    if (cmd == '1') {
      int u, v; cin >> u >> v;
      --u, --v;
      if (++deg[u] == 1) --cnt;
      g[u].emplace(v);
      if (++deg[v] == 1) --cnt;
      g[v].emplace(u);
    } else {
      int v; cin >> v;
      --v;
      cnt += !g[v].empty();
      deg[v] = 0;
      for (auto u : g[v]) {
        g[u].erase(v);
        if (--deg[u] == 0) ++cnt;
      }
      g[v].clear();
    }
    cout << cnt << '\n';
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
