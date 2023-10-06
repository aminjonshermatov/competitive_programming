#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using ld = long double;

void solve() {
  int n;
  cin >> n;
  vector<ld> ps(n);
  for (auto &p : ps) {
    cin >> p;
  }

  vector dp(n + 1, ld(0));
  dp[0] = 1 - ps[0];
  dp[1] = ps[0];
  for (int i = 1; i < n; ++i) {
    vector ndp(n + 1, ld(0));
    for (int j = 0; j < n; ++j) {
      ndp[j] += dp[j] * (1 - ps[i]);
      ndp[j + 1] += dp[j] * ps[i];
    }
    dp.swap(ndp);
  }
  ld tot = 0;
  for (int j = n / 2 + 1; j <= n; ++j) {
    tot += dp[j];
  }
  cout << fixed << setprecision(10) << tot << '\n';
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
