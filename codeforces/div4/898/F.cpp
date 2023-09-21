#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

void solve() {
  i64 n, k;
  cin >> n >> k;
  vector<i64> as(n), hs(n);
  for (auto &a : as) {
    cin >> a;
  }
  for (auto &h : hs) {
    cin >> h;
  }

  int ans = 0;
  i64 cur = 0;
  for (int i = 0, l = 0; i < n; ++i) {
    cur += as[i];
    if (i > 0 && hs[i - 1] % hs[i] != 0) {
      l = i;
      cur = as[i];
    }
    while (l <= i && cur > k) cur -= as[l++];
    if (cur <= k) {
      ans = max(ans, i - l + 1);
    }
  }
  cout << ans << '\n';
}

bool is_multi = true;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
  return 0;
}
