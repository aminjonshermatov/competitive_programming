#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n, m; cin >> n >> m;
  vector<vector<int>> A(m, vector<int>(n));
  for (auto &r : A) for (auto &p : r) cin >> p;
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      bool _any = false;
      for (int r = 0; r < m; ++r) {
        bool ok = false;
        for (int c = 1; c < n; ++c) {
          ok |= A[r][c] == i && A[r][c - 1] == j;
          ok |= A[r][c] == j && A[r][c - 1] == i;
        }
        _any |= ok;
      }
      ans += !_any;
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
