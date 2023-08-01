#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n, k; cin >> n >> k;
  vector<int> ps(k);
  for (auto &p : ps) cin >> p;
  sort(ps.begin(), ps.end());

  vector<array<bool, 2>> dp(n, {false, false});
  for (int x = 1; x <= n; ++x) {
    for (int i = 0; i < k && x >= ps[i]; ++i) {
      for (int y = 0; y < 2; ++y) {
        dp[x][y] |= !dp[x - ps[i]][1 - y];
      }
    }
  }
  for (int x = 1; x <= n; ++x) {
    cout << "LW"[dp[x][0]];
  }
  cout << '\n';
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
