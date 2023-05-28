#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n; cin >> n;
  vector<vector<pair<int, int>>> g(n);
  vector<pair<int, int>> es(n - 1);
  vector<int> cur, used(n, 0), used_e(n - 1, 0);
  used[0] = 1;
  for (int i = 0; i + 1 < n; ++i) {
    auto &[u, v] = es[i];
    cin >> u >> v;
    --u, --v;
    g[u].emplace_back(v, i);
    g[v].emplace_back(u, i);
    if (u == 0 || v == 0) {
      cur.emplace_back(i);
      used_e[i] = 1;
    }
  }

  vector<int> nxt;
  dbg(g);
  auto dfs = [&](auto &f, int v, int t) -> void {
    dbg("dfs", v, t);
    used[v] = 1;
    for (auto [u, tt] : g[v]) {
      if (used[u]) continue;
      if (tt > t) {
        f(f, u, tt);
      } else if (!used_e[tt]) {
        nxt.emplace_back(tt);
        used_e[tt] = 1;
      }
    }
  };
  int ans = 0;
  while (!cur.empty()) {
    ++ans;
    for (auto i : cur) {
      auto [u, v] = es[i];
      if (used[u] + used[v] == 2) continue;
      assert((used[u] + used[v]) == 1);
      if (!used[u]) {
        dfs(dfs, u, i);
      } else {
        dfs(dfs, v, i);
      }
    }
    dbg(cur, nxt, used);
    cur.swap(nxt);
    nxt.clear();
  }
  cout << ans << '\n';
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
