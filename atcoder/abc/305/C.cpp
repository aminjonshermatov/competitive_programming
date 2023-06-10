#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int h, w; cin >> h >> w;
  int x_mn = 1e9, x_mx = -1, y_mn = 1e9, y_mx = -1;
  vector<string> g(h);
  for (int i = 0; i < h; ++i) {
    cin >> g[i];
    for (int j = 0; j < w; ++j) {
      if (g[i][j] == '#') {
        x_mn = min(x_mn, j);
        x_mx = max(x_mx, j);
        y_mn = min(y_mn, i);
        y_mx = max(y_mx, i);
      }
    }
  }

  int cnt = 0;
  pair<int, int> ans{-1,-1};
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      if (g[i][j] == '.' && clamp(i, y_mn, y_mx) == i && clamp(j, x_mn, x_mx) == j) {
        ++cnt;
        ans = pair(i + 1, j + 1);
      }
    }
  }
  assert(cnt == 1);
  cout << ans.first << ' ' << ans.second << '\n';
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
