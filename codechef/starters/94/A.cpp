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
  int om = 0, addy = 0, cur = 0;
  for (int i = 0; i < n; ++i) {
    int x; cin >> x;
    if (x > 0) ++cur;
    else {
      om = max(om, cur);
      cur = 0;
    }
  }
  om = max(om, cur);
  cur = 0;
  for (int i = 0; i < n; ++i) {
    int x; cin >> x;
    if (x > 0) ++cur;
    else {
      addy = max(addy, cur);
      cur = 0;
    }
  }
  addy = max(addy, cur);
  if (om == addy) {
    cout << "DRAW\n";
  } else if (om < addy) {
    cout << "ADDY\n";
  } else {
    cout << "OM\n";
  }
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
