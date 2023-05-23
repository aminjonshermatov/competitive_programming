#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

void solve() {
  int n;
  i64 W;
  cin >> n >> W;
  array<map<i64, i64>, 2> dp{};
  int tp = 0;
  dp[tp][0] = 0;
  for (int i = 0; i < n; ++i) {
    i64 w, v;
    cin >> w >> v;
    tp ^= 1;
    dp[tp].clear();
    for (auto [pw, pv] : dp[tp ^ 1]) {
      dp[tp][pw] = max(dp[tp][pw], pv);
      if (w + pw <= W) {
        dp[tp][w + pw] = max(dp[tp][w + pw], pv + v);
      }
    }
  }

  i64 ans = 0;
  for (auto [_, pv] : dp[tp]) {
    ans = max(ans, pv);
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
