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
  i64 x, y;
  cin >> n >> x >> y;

  vector<i64> ps(n - 1), ts(n - 1);
  for (int i = 0; i + 1 < n; ++i) {
    cin >> ps[i] >> ts[i];
  }

  constexpr auto inf = 1e15;
  vector<array<i64, 9>> dp(n);
  for (auto &r : dp) {
    r.fill(inf);
  }
  dp[n - 1].fill(0);

  for (int i = n - 2; i >= 0; --i) {
    for (int a = 1; a <= 8; ++a) {
      for (int b = 1; b <= 8; ++b) {
        auto t = ts[i] + a;
        auto r = t % b;
        if (r != 0) r = b - r;
        assert((t + r) % b == 0);
        dp[i][a] = min(dp[i][a], abs(a - ps[i]) + dp[i + 1][b] + ts[i] + r);
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int a = 1; a <= 8; ++a) {
      cout << dp[i][a] << ' ';
    }
    cout << '\n';
  }

  int q;
  cin >> q;
  for (int i = 0; i < q; ++i) {
    int s;
    cin >> s;
    i64 tot = inf;
    for (int a = 1; a <= 8; ++a) {
      i64 loc = s + x;
      auto r = loc % a;
      if (r != 0) loc += abs(a - r);
      loc += dp[0][a];
      if (i == 1 && tot > loc + y) {
        dbg(a, loc);
      }
      tot = min(tot, loc + y);
    }
    cout << tot << '\n';
  }
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
