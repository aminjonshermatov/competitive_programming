#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n; cin >> n;
  string s; cin >> s;
  if (n == 1) {
    cout << 2 << '\n';
    return;
  }
  int ans = 0, cur = 1;
  for (int i = 1; i < n; ++i) {
    if (s[i] == s[i - 1]) ++cur;
    else cur = 1;
    ans = max(ans, cur + 1);
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
