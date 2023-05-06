// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

constexpr inline array<int, 5> dk{1, 0, -1, 0, 1};

void solve() {
  int n, m; cin >> n >> m;
  vector<vector<int>> g(n, vector<int>(m));
  for (auto &r : g) {
    for (auto &x : r) {
      cin >> x;
    }
  }

  auto ok = [&n, &m](int i, int j) -> bool {
    return clamp(i, 0, n - 1) == i && clamp(j, 0, m - 1) == j;
  };
  auto dfs = [&](auto &f, int i, int j) -> int {
    int cur = g[i][j];
    g[i][j] = 0;
    for (int k = 0; k < 4; ++k) {
      auto ni = i + dk[k];
      auto nj = j + dk[k + 1];
      if (!ok(ni, nj) || g[ni][nj] == 0) continue;
      cur += f(f, ni, nj);
    }
    return cur;
  };

  int ans = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (g[i][j] > 0) {
        ans = max(ans, dfs(dfs, i, j));
      }
    }
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
