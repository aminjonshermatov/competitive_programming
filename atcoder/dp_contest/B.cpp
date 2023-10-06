#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n, k;
  cin >> n >> k;
  vector<int> hs(n);
  for (auto &x : hs) {
    cin >> x;
  }

  vector dp(n, numeric_limits<int>::max());
  dp[0] = 0;
  for (int i = 1; i < n; ++i) {
    for (int j = 1; j <= k && i - j >= 0; ++j) {
      dp[i] = min(dp[i], dp[i - j] + abs(hs[i] - hs[i - j]));
    }
  }
  cout << dp.back() << '\n';
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
