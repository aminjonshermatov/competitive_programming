#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

void solve() {
  int n; cin >> n;
  vector<vector<int>> g(n);
  for (int v = 0; v < n; ++v) {
    int c; cin >> c;
    for (int j = 0; j < c; ++j) {
      int u; cin >> u;
      --u;
      g[v].emplace_back(u);
    }
  }
  vector<int> ans;
  vector<bool> used(n, false);
  auto dfs = [&](auto &f, int v) -> void {
    used[v] = true;
    for (auto u : g[v]) {
      if (used[u]) continue;
      f(f, u);
    }
    ans.push_back(v);
  };
  dfs(dfs, 0);
  ans.pop_back();
  for (auto v : ans) {
    cout << v + 1 << ' ';
  }
  cout << '\n';
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
