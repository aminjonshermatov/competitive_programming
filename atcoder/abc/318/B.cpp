#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  vector<vector<int>> g(101, vector<int>(101, 0));
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    for (int x = a; x < b; ++x) {
      for (int y = c; y < d; ++y) {
        ++g[x][y];
      }
    }
  }
  int ans = 0;
  for (int i = 0; i < 101; ++i) {
    for (int j = 0; j < 101; ++j) {
      ans += g[i][j] > 0;
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
