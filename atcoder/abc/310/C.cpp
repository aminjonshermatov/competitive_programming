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
  set<string> used;
  for (int i = 0; i < n; ++i) {
    string s; cin >> s;
    if (used.count(s) > 0) continue;
    reverse(s.begin(), s.end());
    if (used.count(s) > 0) continue;
    used.emplace(s);
  }
  cout << used.size() << '\n';
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
