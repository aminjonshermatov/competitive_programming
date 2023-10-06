#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

void solve() {
  i64 n, w;
  cin >> n >> w;
  vector<i64> ws(n), vs(n);
  for (int i = 0; i < n; ++i) {
    cin >> ws[i] >> vs[i];
  }

  constexpr auto  inf = numeric_limits<i64>::max();
  constexpr auto ninf = numeric_limits<i64>::min();
  auto ans = ninf;
  const auto maxProfit = accumulate(vs.begin(), vs.end(), i64(0));
  vector dp(maxProfit + 1, inf);
  dp[0] = 0;
  for (int i = 0; i < n; ++i) {
    auto ndp = dp;
    for (auto j = vs[i]; j <= maxProfit; ++j) {
      if (dp[j - vs[i]] == inf || dp[j - vs[i]] + ws[i] > w) continue;
      ndp[j] = min(ndp[j], dp[j - vs[i]] + ws[i]);
    }
    dp.swap(ndp);
    for (i64 j = 0; j <= maxProfit; ++j) {
      if (dp[j] != inf) {
        ans = max(ans, j);
      }
    }
  }
  cout << ans << '\n';
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
