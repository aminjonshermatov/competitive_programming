#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n, m; cin >> n >> m;
  vector<string> g(n);
  for (auto &r : g) cin >> r;

  auto ok = [&](int i, int j) -> bool {
    for (int ii = 0; ii < 3; ++ii) {
      for (int jj = 0; jj < 3; ++jj) {
        if (g[i + ii][j + jj] != '#') {
          return false;
        }
      }
    }
    for (int ii = 0; ii < 3; ++ii) {
      for (int jj = 0; jj < 3; ++jj) {
        if (g[i + 8 - ii][j + 8 - jj] != '#') {
          return false;
        }
      }
    }

    for (int ii = 0; ii < 4; ++ii) {
      if (g[i + ii][j + 3] != '.') {
        return false;
      }
      if (g[i + 8 - ii][j + 8 - 3] != '.') {
        return false;
      }
    }
    for (int jj = 0; jj < 3; ++jj) {
      if (g[i + 3][j + jj] != '.') {
        return false;
      }
      if (g[i + 8 - 3][j + 8 - jj] != '.') {
        return false;
      }
    }
    return true;
  };

  for (int i = 0; i + 8 < n; ++i) {
    for (int j = 0; j + 8 < m; ++j) {
      if (ok(i, j)) {
        cout << i + 1 << ' ' << j + 1 << '\n';
      }
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
