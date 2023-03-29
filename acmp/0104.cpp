// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  string s, p;
  cin >> s >> p;

  if (s.find('*') != string::npos || s.find('?') != string::npos) {
    swap(s, p);
  }

  const int n(s.size());
  const int m(p.size());

  vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
  dp[0][0] = true;
  for (int j = 1; j <= m; ++j) {
    if (p[j - 1] == '*') dp[0][j] = dp[0][j - 1];
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      if (s[i - 1] == p[j - 1] || p[j - 1] == '?') {
        dp[i][j] = dp[i - 1][j - 1];
      } else {
        if (p[j - 1] == '*') {
          dp[i][j] = dp[i][j - 1] || dp[i - 1][j] || dp[i - 1][j - 1];
        }
      }
    }
  }

  cout << (dp[n][m] ? "YES" : "NO") << '\n';
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