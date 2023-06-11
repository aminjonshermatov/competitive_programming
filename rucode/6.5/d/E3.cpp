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
  vector<vector<int>> g(n);
  int root = -1;
  for (int i = 0; i < n; ++i) {
    int p; cin >> p;
    if (p == 0) {
      root = p;
      continue;
    }
    --p;
    g[i].emplace_back(p);
    g[p].emplace_back(i);
  }

  auto dfs = [&](auto &f, int v, int p) -> array<int, 2> {
    array<int, 2> loc{};
    loc[0] = 1;
    loc[1] = 0;
    for (auto u : g[v]) {
      if (u == p) continue;
      auto [with, wout] = f(f, u, v);
      loc[0] += wout;
      loc[1] += max(with, wout);
    }
    return loc;
  };

  auto [with, wout] = dfs(dfs, root, -1);
  cout << max(with, wout) << '\n';
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
