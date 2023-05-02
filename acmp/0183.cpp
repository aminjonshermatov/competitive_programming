// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int k, p;
  cin >> k >> p;

  vector<int> dp(k + 1, 0);
  dp[2] = 1 % p;
  for (int i = 2; i < k; ++i) {
    if (i + 1 <= k) dp[i + 1] = (dp[i + 1] + dp[i]) % p;
    if (2 * i <= k) dp[2 * i] = (dp[2 * i] + dp[i]) % p;
  }
  cout << dp[k] << '\n';
}

bool is_multi = false;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
}