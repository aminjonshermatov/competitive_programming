#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

inline constexpr array<int, 4> dx{-1, 0, 0, 1};
inline constexpr array<int, 4> dy{0, -1, +1, 0};

void solve() {
  int n, m; cin >> n >> m;
  vector<string> g(n);
  for (auto &r : g) cin >> r;

  auto ok = [&](int i, int j) -> bool {
    return clamp(i, 0, n - 1) == i && clamp(j, 0, m - 1) == j;
  };

  vector<vector<array<bool, 4>>> used(n, vector<array<bool, 4>>(m));
  for (auto &r : used) for (auto &x : r) x.fill(false);

  auto dfs = [&](auto &f, int i, int j, int t) -> void {
    used[i][j][t] = true;
    auto ni = i + dy[t];
    auto nj = j + dx[t];
    assert(ok(ni, nj));
    if (g[ni][nj] == '.') {
      if (!used[ni][nj][t]) {
        f(f, ni, nj, t);
      }
    } else {
      for (int nt = 0; nt < 4; ++nt) {
        ni = i + dy[nt];
        nj = j + dx[nt];
        if (ok(ni, nj) && g[ni][nj] == '.' && !used[ni][nj][nt]) {
          f(f, ni, nj, nt);
        }
      }
    }
  };
  used[1][1][0] = true;
  for (int t = 0; t < 4; ++t) {
    auto ni = 1 + dy[t];
    auto nj = 1 + dx[t];
    if (ok(ni, nj) && g[ni][nj] == '.' && !used[ni][nj][t]) {
      dfs(dfs, ni, nj, t);
    }
  }
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      // ans += any_of(used[i][j].begin(), used[i][j].end(), identity());
      ans += any_of(used[i][j].begin(), used[i][j].end(), [](auto x) { return x; });
    }
  }
  cout << ans << '\n';
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
