#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n; cin >> n;
  vector<int> as(n);
  for (auto &a : as) {
    cin >> a;
    --a;
  }

  vector<int> color(n, 0), prv(n, -1);
  int ce = -1, cs = -1;
  auto dfs = [&](auto &f, int v) -> bool {
    color[v] = 1;
    if (color[as[v]] == 0) {
      if (f(f, as[v])) {
        prv[as[v]] = v;
        return true;
      }
    } else if (color[as[v]] == 1) {
      ce = v;
      cs = as[v];
      return true;
    }
    color[v] = 2;
    return false;
  };

  for (int v = 0; v < n; ++v) {
    if (color[v] == 0 && dfs(dfs, v)) {
      vector<int> path;
      path.push_back(cs);
      for (int u = ce; u != cs && u != -1; u = prv[u]) {
        path.push_back(u);
      }
      reverse(path.begin(), path.end());

      cout << path.size() << '\n';
      for (auto u : path) {
        cout << u + 1 << ' ';
      }
      cout << '\n';
      return;
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
