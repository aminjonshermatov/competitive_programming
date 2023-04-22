// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n; cin >> n;
  string s; cin >> s;

  if (count(s.begin(), s.end(), 'o') == 0 || count(s.begin(), s.end(), '-') == 0) {
    cout << -1 << '\n';
    return ;
  }

  int ans = -1;
  int l = 0;
  for (int i = 0; i < n; ++i) {
    if (s[i] == '-') {
      ans = max(ans, i - l);
      l = i + 1;
    }
  }
  ans = max(ans, n - l);
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
