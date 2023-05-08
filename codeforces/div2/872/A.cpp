// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  string s; cin >> s;
  if (std::count(s.begin(), s.end(), s.front()) == s.size()) {
    cout << -1 << '\n';
    return;
  }
  bool is_pal = true;
  for (int i = 0; i < s.size()/2; ++i) {
    is_pal &= s[i] == s[s.size() - i - 1];
  }
  cout << s.size() - is_pal << '\n';
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
