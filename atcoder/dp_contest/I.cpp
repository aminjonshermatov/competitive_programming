#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

using ld = long double;

void solve() {
  int n; cin >> n;
  vector<ld> P(n);
  for (auto &p : P) cin >> p;

  vector<vector<ld>> dp(n, vector<ld>(n + 1));
  dp[0][0] = 1 - P[0];
  dp[0][1] = P[0];
  for (int i = 1; i < n; ++i) {
    for (int j = 0; j <= i; ++j) {
      dp[i][j] += dp[i - 1][j] * (1 - P[i]);
      dp[i][j + 1] += dp[i - 1][j] * P[i];
    }
  }

  ld ans = 0;
  for (int i = n / 2 + (n & 1); i <= n; ++i) {
    ans += dp[n - 1][i];
  }
  cout << fixed << setprecision(10) << ans << '\n';
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
