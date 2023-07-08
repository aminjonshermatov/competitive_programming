#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int a, b; cin >> a >> b;
  cout << ((a + 1 == b && clamp(b, 2, 3) == b) || (a + 1 == b && clamp(b, 5, 6) == b) || (a + 1 == b && clamp(b, 8, 9) == b) ? "Yes" : "No") << '\n';
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
