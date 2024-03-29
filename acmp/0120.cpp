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

  vector<int> dp(M[0]);
  for (int i = 1; i < m; ++i) {
    dp[i] += dp[i - 1];
  }

  for (int i = 1; i < n; ++i) {
    vector<int> ndp(m);
    for (int j = 0; j < m; ++j) {
      auto mn = dp[j];
      if (j > 0) mn = min(mn, ndp[j - 1]);
      ndp[j] = mn + M[i][j];
    }
    dp.swap(ndp);
  }
  cout << dp[m - 1] << '\n';
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