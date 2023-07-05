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
  int cnt = 0;
  for (int i = 0; i < n; ++i) {
    if (s[i] == ':') {
      while (i + 1 < n && s[i + 1] == ')') ++i;
      cnt += i + 1 < n && s[i] == ')' && s[i + 1] == ':';
    }
  }
  cout << cnt << '\n';
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
