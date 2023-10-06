#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n;
  cin >> n;
  vector vs(n, array<int, 3>{});
  for (auto &r : vs) {
    for (auto &x : r) {
      cin >> x;
    }
  }

  const auto ninf = numeric_limits<int>::min();
  auto dp = vs[0];
  for (int i = 1; i < n; ++i) {
    decltype(dp) ndp;
    for (int a = 0; a < 3; ++a) {
      ndp[a] = ninf;
      for (int b = 0; b < 3; ++b) {
        if (a == b) continue;
        ndp[a] = max(ndp[a], dp[b] + vs[i][a]);
      }
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
