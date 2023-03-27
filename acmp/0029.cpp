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
  vector<int> H(n);
  for (auto &h : H) {
    cin >> h;
  }

  vector<int> dp(n);
  dp[0] = 0;
  for (int i = 1; i < n; ++i) {
    auto mn = abs(H[i] - H[i - 1]) + dp[i - 1];
    if (i > 1) mn = min(mn, 3 * abs(H[i] - H[i - 2]) + dp[i - 2]);
    dp[i] = mn;
  }
  cout << dp[n - 1] << '\n';
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