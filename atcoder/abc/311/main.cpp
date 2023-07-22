#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

void solve() {
  int n, m; cin >> n >> m;
  vector<vector<int>> g(n, vector<int>(m));
  for (auto &r : g) {
    for (auto &x : r) {
      cin >> x;
    }
  }

  i64 ans = 0;
  for (int l1 = 0; l1 < n; +l1) {
    for (int l2 = l1; l2 < n; ++l2) {

      for (int i = 0; i < n; ++i) {

      }
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
