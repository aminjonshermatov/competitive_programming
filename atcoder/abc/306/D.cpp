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
  int n; cin >> n;
  vector<int> X(n), Y(n);
  for (int i = 0; i < n; ++i) {
    cin >> X[i] >> Y[i];
  }

  vector<array<i64, 2>> cache(n);
  vector<array<bool, 2>> seen(n, {false, false});
  auto dp = [&](auto &f, int i, bool is_healthy) -> i64 {
    if (i >= n) return 0;
    if (seen[i][is_healthy]) return cache[i][is_healthy];

    auto loc = max<i64>(0, f(f, i + 1, is_healthy));
    if (X[i] == 0) {
      loc = max(loc, f(f, i + 1, true) + Y[i]);
    } else {
      if (is_healthy) {
        loc = max(loc, f(f, i + 1, false) + Y[i]);
      }
    }
    seen[i][is_healthy] = true;
    return cache[i][is_healthy] = loc;
  };
  cout << dp(dp, 0, true) << '\n';
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
