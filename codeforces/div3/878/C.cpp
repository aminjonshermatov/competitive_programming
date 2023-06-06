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
  int n, k, q; cin >> n >> k >> q;
  i64 cur = 0, ans = 0;
  for (int i = 0; i < n; ++i) {
    int t; cin >> t;
    if (t > q) {
      if (cur > 0) {
        if (cur >= k) {
          auto d = cur - k + 1;
          ans += d * (d + 1) / 2;
        }
      }
      cur = 0;
    } else {
      ++cur;
    }
  }
  if (cur > 0) {
    if (cur >= k) {
      dbg(cur);
      auto d = cur - k + 1;
      ans += d * (d + 1) / 2;
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
