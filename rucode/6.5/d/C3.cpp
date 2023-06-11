#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

constexpr auto inf = numeric_limits<int>::max();

void solve() {
  int n, k; cin >> n >> k;
  --k;
  vector<vector<int>> g(n);
  for (int i = 1; i < n; ++i) {
    int u, v; cin >> u >> v;
    --u, --v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }

  int ans = inf;
  auto dfs = [&](auto &f, int v, int p, int which) -> array<bool, 2> {
    array<bool, 2> loc{};
    assert(clamp(which, 0, 1) == which);
    loc[which] = false;
    loc[1 ^ which] = true;
    for (auto u : g[v]) {
      if (u == p) continue;
      auto tmp = f(f, u, v, 1 ^ which);
      if (tmp[which]) {
        loc = tmp;
        if (v == k) ans = min(ans, u);
      }
    }
    return loc;
  };
  dfs(dfs, k, -1, 0);
  if (ans == inf) {
    cout << "First player loses\n";
    return;
  }
  cout << "First player wins flying to airport " << ans + 1 << '\n';
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
