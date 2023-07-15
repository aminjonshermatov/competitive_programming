#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n, p, q; cin >> n >> p >> q;
  int mn = 1e9;
  for (int i = 0; i < n; ++i) {
    int x; cin >> x;
    mn = min(mn, x);
  }
  dbg(mn);
  cout << min(p, mn + q) << '\n';
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
