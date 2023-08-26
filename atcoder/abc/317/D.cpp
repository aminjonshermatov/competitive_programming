#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

void solve() {
  int n; cin >> n;
  vector<i64> X(n), Y(n), Z(n);
  for (int i = 0; i < n; ++i) {
    cin >> X[i] >> Y[i] >> Z[i];
  }
  constexpr auto inf = numeric_limits<i64>::max();
  const auto sm = accumulate(Z.begin(), Z.end(), i64(0));
  vector<i64> dp(sm + 1, inf);
  dp[0] = 0;
  for (int i = 0; i < n; ++i) {
    vector<i64> ndp = dp;
    for (int w = Z[i]; w <= sm; ++w) {
      if (dp[w - Z[i]] == inf) continue;
      ndp[w] = min(ndp[w], dp[w - Z[i]] + max(i64(0), (X[i] + Y[i] + 1) / 2 - X[i]));
    }
    dp.swap(ndp);
    dbg(dp);
  }
  cout << *min_element(dp.begin() + (sm + 1) / 2, dp.end()) << '\n';
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
