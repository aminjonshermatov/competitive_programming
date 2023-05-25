#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int x, k; cin >> x >> k;
  if (x % k != 0) {
    cout << 1 << '\n' << x << '\n';
  } else {
    if (x - 1 > 0) {
      cout << 2 << '\n' << x - 1 << ' ' << 1 << '\n';
    } else {
      cout << 1 << '\n' << x - 1 << '\n';
    }
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
