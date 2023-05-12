#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  string s; cin >> s;
  set<char> seen;
  for (int i = 0; i < s.size() / 2; ++i) {
    if (i > 0 && seen.count(s[i]) == 0) {
      cout << "YES\n";
      return;
    }
    seen.emplace(s[i]);
  }
  cout << "NO\n";
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
