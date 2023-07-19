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
  i64 ans = 0;
  vector<i64> cnt(n, 0);
  i64 cur = 0;
  for (int i = 0; i < n; ++i) {
    int x; cin >> x;
    --x;
    if (++cnt[x] & 1) cur += 1;
    else cur -= 1;
    ans = max(ans, cur);
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
