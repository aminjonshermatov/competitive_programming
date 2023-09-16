#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

void solve() {
  string s;
  cin >> s;

  const auto n = int(s.size());
  int ans = 0;
  for (int len = 1; len <= n; ++len) {
    for (int i = 0; i + len - 1 < n; ++i) {
      auto ss = s.substr(i, len);
      auto rss = ss;
      reverse(rss.begin(), rss.end());
      if (ss == rss) {
        ans = max(ans, len);
      }
    }
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
