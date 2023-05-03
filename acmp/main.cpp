// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using u64 = ::uint64_t;

u64 solve(int n) {
  u64 all_set = (1ull << (n + 1)) - 1;
  int offset = 2;
  auto dp = [&](auto &f, int last, u64 used) -> u64 {
    if ((used & all_set) == all_set) return 1;
    u64 loc = 0;
    for (int nw = max(0, last - offset); nw <= min(n, last + offset); ++nw) {
      if ((used >> nw) & 1) continue;
      loc += f(f, nw, used | (1ull << nw));
    }
    return loc;
  };
  return dp(dp, 1, 0b11);
}

void solve() {
  /*
  // 1 1 2 4 6 9 14 21 31 46
  for (int n = 1; n <= 10; ++n) {
    cout << solve(n) << " \n"[n == 10];
  }*/
  int n; cin >> n;
  vector<u64> dp(max(3, n));
  dp[0] = dp[1] = 1;
  dp[2] = 2;
  for (int i = 3; i < n; ++i) {
    dp[i] = dp[i - 1] + dp[i - 3] + 1;
  }
  cout << dp[n - 1] << '\n';
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