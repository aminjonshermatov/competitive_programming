#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int prv = -1e9;
  bool ok = true;
  for (int i = 0; i < 8; ++i) {
    int x; cin >> x;
    ok &= x >= prv && clamp(x, 100, 675) == x && x % 25 == 0;
    prv = x;
  }
  cout << (ok ? "Yes" : "No") << '\n';
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
