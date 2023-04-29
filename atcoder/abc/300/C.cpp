// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int h, w; cin >> h >> w;
  vector<string> C(h);
  for (auto &r : C) cin >> r;

  auto is_fit_in = [&](int i, int j) -> bool {
    return clamp(i, 0, h - 1) == i && clamp(j, 0, w - 1) == j;
  };

  auto ok = [&](int i, int j, int d) -> bool {
    for (int k = 0; k <= d; ++k) {
      if (C[i + k][j + k] != '#') return false;
      if (C[i + k][j - k] != '#') return false;
      if (C[i - k][j + k] != '#') return false;
      if (C[i - k][j - k] != '#') return false;
    }
    if (!is_fit_in(i + d + 1, j + d + 1) || !is_fit_in(i + d + 1, j - d - 1) || !is_fit_in(i - d - 1, j + d + 1) || !is_fit_in(i - d - 1, j - d - 1)) {
      return true;
    }
    return C[i + d + 1][j + d + 1] == '.' || C[i + d + 1][j - d - 1] == '.' || C[i - d - 1][j + d + 1] == '.' || C[i - d - 1][j - d - 1] == '.';
  };

  auto cnt = [&](int d) -> int {
    int ans = 0;
    for (int i = d; i + d < h; ++i) {
      for (int j = d; j + d < w; ++j) {
        ans += ok(i, j, d);
      }
    }

    return ans;
  };

  int n = min(h, w);
  for (int i = 0; i < n; ++i) {
    cout << cnt(i + 1) << ' ';
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
