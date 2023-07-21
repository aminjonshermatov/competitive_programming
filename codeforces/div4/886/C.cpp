#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n = 8;
  string ans;
  for (int i = 0; i < n; ++i) {
    string s; cin >> s;
    for (int j = 0; j < n; ++j) {
      if (isalpha(s[j])) {
        ans.push_back(s[j]);
      }
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
