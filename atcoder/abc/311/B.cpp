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

  int ans = 0, cur = 0;
  for (int j = 0; j < m; ++j) {
    bool ok = true;
    for (int i = 0; i < n; ++i) {
      ok &= g[i][j] == 'o';
    }
    if (ok) {
      ++cur;
    } else {
      cur = 0;
    }
    ans = max(ans, cur);
  }
  cout << max(ans, cur) << '\n';
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
