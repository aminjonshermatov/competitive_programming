#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  string s;
  cin >> s;
  string x = "383";
  int cnt = 0;
  for (int i = 0; i < 3; ++i) {
    cnt += s[i] != x[i];
  }
  cout << (cnt == 0 || cnt == 2 ? "YES" : "NO") << '\n';
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
