#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

struct Pt { int x, y; };

void solve() {
  int n; cin >> n;
  vector<Pt> pts(n);
  for (auto &[x, y] : pts) {
    cin >> x >> y;
  }

  using ld = long double;
  auto dist = [&](int i, int j) -> ld {
    auto dx = abs(pts[i].x - pts[j].x);
    auto dy = abs(pts[i].y - pts[j].y);
    return sqrt(dx * dx + dy * dy);
  };
  constexpr int LIMIT = 35;

  vector<vector<ld>> dp(n, vector<ld>(LIMIT, 1e10));
  dp[0][0] = 0;
  for (int i = 1; i < n; ++i) {
    for (int prv = 0; prv < LIMIT; ++prv) {
      for (int skip = 0; skip + prv < LIMIT && i - 1 - skip >= 0; ++skip) {
        dp[i][prv + skip] = min(dp[i][prv + skip], dp[i - 1 - skip][prv] + dist(i - 1 - skip, i));
      }
    }
  }
  ld ans = 1e10;
  for (int skip = 0; skip < LIMIT; ++skip) {
    ans = min(ans, dp[n - 1][skip] + (skip == 0 ? 0 : (1ll << (skip - 1))));
  }
  cout << fixed << setprecision(10) << ans << '\n';
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
