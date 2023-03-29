// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n; cin >> n;
  vector<string> g(n);
  for (auto &r : g) {
    cin >> r;
  }

  vector<vector<int>> leftZero(n + 1, vector<int>(n + 1, 0));
  for (int i = 1; i <= n; ++i) {
    int z = 0;
    for (int j = 1; j <= n; ++j) {
      if (g[i - 1][j - 1] == '0') z = j;
      leftZero[i][j] = z;
    }
  }

  vector<vector<int>> topZero(n + 1, vector<int>(n + 1, 0));
  for (int j = 1; j <= n; ++j) {
    int z = 0;
    for (int i = 1; i <= n; ++i) {
      if (g[i - 1][j - 1] == '0') z = i;
      topZero[i][j] = z;
    }
  }

  int ans = 0;
  vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      dp[i][j] = min({
        i - topZero[i][j],
        j - leftZero[i][j],
        dp[i - 1][j - 1] + 1
      });
      ans = max(ans, dp[i][j] * dp[i][j]);
    }
  }

  cout << ans << '\n';
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