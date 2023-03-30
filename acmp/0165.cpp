// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n, m; cin >> n >> m;
  vector<vector<int>> M(n, vector<int>(m));
  for (auto &r : M) {
    for (auto &x : r) {
      cin >> x;
    }
  }

  auto is_safe = [&](int i, int j) -> bool {
    return clamp(i, 0, n - 1) == i && clamp(j, 0, m - 1) == j;
  };

  vector<vector<int>> dp(n, vector<int>(m, 0));
  dp[0][0] = 1;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (M[i][j] == 0) continue ;
      if (is_safe(i + M[i][j], j)) dp[i + M[i][j]][j] += dp[i][j];
      if (is_safe(i, j + M[i][j])) dp[i][j + M[i][j]] += dp[i][j];
    }
  }

  cout << dp[n - 1][m - 1] << '\n';
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