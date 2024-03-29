#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

void solve() {
  int n;
  i64 w;
  cin >> n >> w;
  vector<int> ws(n);
  vector<i64> vs(n);
  for (int i = 0; i < n; ++i) {
    cin >> ws[i] >> vs[i];
  }

  constexpr auto ninf = numeric_limits<i64>::min();
  vector<i64> dp(w + 1, ninf);
  dp[0] = 0;
  for (int i = 0; i < n; ++i) {
    decltype(dp) ndp = dp;
    for (int j = ws[i]; j <= w; ++j) {
      ndp[j] = max(ndp[j], dp[j - ws[i]] + vs[i]);
    }
    dp.swap(ndp);
  }
  cout << *max_element(dp.begin(), dp.end()) << '\n';
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
