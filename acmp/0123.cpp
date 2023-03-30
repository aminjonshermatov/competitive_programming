// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  string s; cin >> s;
  const int n(s.size());

  // dp[index][balance]
  // dp[n - 1][0]
  vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
  dp[0][0] = 1;
  for (int i = 1; i <= n; ++i) {
    if (s[i - 1] == '(') {
      for (int bal = 1; bal <= n; ++bal) {
        dp[i][bal] += dp[i - 1][bal - 1];
      }
    } else if (s[i - 1] == ')') {
      for (int bal = 0; bal < n; ++bal) {
        dp[i][bal] += dp[i - 1][bal + 1];
      }
    } else {
      for (int bal = 0; bal <= n; ++bal) {
        dp[i][bal] += (bal > 0 ? dp[i - 1][bal - 1] : 0) + (bal < n ? dp[i - 1][bal + 1] : 0);
      }
    }
  }

  cout << dp[n][0] << '\n';
}

//#define MEASURE_TIME
bool is_multi = false;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
#ifdef MEASURE_TIME
  auto start = chrono::steady_clock::now();
#endif
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
#ifdef MEASURE_TIME
  auto finish = chrono::steady_clock::now();
  auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(finish - start);
  cerr << endl << "Time: " << elapsed_ms.count() << " ms\n";
#endif
  return 0;
}